using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace HBH.Audio.IO
{
    public static class Wave
    {
        public static Stream CreateNewWaveFile(string path , byte[] data , FMTChunk fmt)
        {
            FileStream s = File.Create(path,data.Count(),FileOptions.SequentialScan);
            s.Lock(0, data.Count());
            s.Write(Encoding.ASCII.GetBytes("RIFF"), 0, 4);
            var st = BitConverter.GetBytes(data.Count() + fmt.Size + 16);
            st.Reverse();
            s.Write(st, 0, st.Length);
            s.Write(Encoding.ASCII.GetBytes("WAVE"), 0, 4);
            s.Write(Encoding.ASCII.GetBytes("fmt "), 0, 4);
            var b = new byte[4 * 5];    //3 ints (4 * 3) and 4 shorts (2 * 4) = 4 * 5.
            st = BitConverter.GetBytes(fmt.Size);
            st.Reverse();
            st.CopyTo(b, 0);
            BitConverter.GetBytes(fmt.AudioFormat).CopyTo(b, 4);
            BitConverter.GetBytes(fmt.NumChannels).CopyTo(b, 6);
            BitConverter.GetBytes(fmt.SampleRate).CopyTo(b, 8);
            BitConverter.GetBytes(fmt.ByteRate).CopyTo(b, 12);
            BitConverter.GetBytes(fmt.BlockAlign).CopyTo(b, 16);
            BitConverter.GetBytes(fmt.BitsPerSample).CopyTo(b, 18);
            s.Write(b, 0, 20);
            s.Write(Encoding.ASCII.GetBytes("data"), 0, 4);
            st = BitConverter.GetBytes(data.Length + fmt.Size);
            st.Reverse();
            s.Write(st, 0, 4);
            s.Write(data, 0, data.Count());
            return s;
        }
        [System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential,
            CharSet = System.Runtime.InteropServices.CharSet.Ansi, Size = 8)]
        public struct RIFFChunk
        {
            public char[] ID;
            public int Size;
            public char[] Format;
            public RIFFChunk(char[] id, int size, char[] format)
            {
                ID = id;
                Size = size;
                Format = format;
            }
        }
        public static RIFFChunk ReadRiff(Stream file)
        {
            file.Position = 0;
            RIFFChunk riff = new RIFFChunk();
            byte[] b = new byte[4];
            file.Read(b, 0, 4);
            if (Encoding.ASCII.GetString(b) == "RIFF")
            {
                riff.ID = "RIFF".ToCharArray();
                file.Read(b, 0, 4);
                riff.Size = BitConverter.ToInt32(b, 0);
                file.Read(b, 0, 4);
                riff.Format = Encoding.ASCII.GetString(b).ToCharArray();
            }
            else
            {
                riff.ID = "ERR!".ToCharArray();
                riff.Format = "EMPT".ToCharArray();
            }
            return riff;
        }
        [System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential
            , CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct FMTChunk
        {
            public char[] ID;
            public int Size;
            public short AudioFormat;
            public short NumChannels;
            public int SampleRate;
            public int ByteRate;
            public short BlockAlign;
            public short BitsPerSample;
        }
        public static FMTChunk ReadFMT(Stream file)
        {
            FMTChunk fmt = new FMTChunk();
            byte[] b = new byte[4];
            if (file.Position != 12) file.Seek(12, SeekOrigin.Begin);
            file.Read(b, 0, 4);
            if (Encoding.ASCII.GetString(b) == "fmt ")
            {
                fmt.ID = "fmt ".ToCharArray();
                file.Read(b, 0, 4);
                fmt.Size = BitConverter.ToInt32(b, 0);
                b = new byte[fmt.Size];
                file.Read(b, 0, fmt.Size);
                fmt.AudioFormat = BitConverter.ToInt16(b, 0);
                fmt.NumChannels = BitConverter.ToInt16(b, 2);
                fmt.SampleRate = BitConverter.ToInt32(b, 4);
                fmt.ByteRate = BitConverter.ToInt32(b, 8);
                fmt.BlockAlign = BitConverter.ToInt16(b, 12);
                fmt.BitsPerSample = BitConverter.ToInt16(b, 14);
            }
            return fmt;
        }
        [System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Sequential
            , CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct DATAChunk
        {
            public char[] ID;
            public int Size;
            public byte[] Data;
            public System.Runtime.InteropServices.GCHandle Handle { get; internal set; }
            public IntPtr DataToPtr()
            {
                return Handle.AddrOfPinnedObject();
            }
            public void FreeHandle()
            {
                Handle.Free();
            }
        }
        public static DATAChunk ReadData(Stream file)
        {
            file.Position = 36;
            DATAChunk data = new DATAChunk();
            byte[] b = new byte[4];
            file.Read(b, 0, 4);
            char[] id = Encoding.ASCII.GetChars(b);
            if(Encoding.ASCII.GetString(b) != "data")
            {
                file.Read(b, 0, 4);
                id = Encoding.ASCII.GetChars(b);
            }
            data.ID = id;
            file.Read(b, 0, 4);
            data.Size = BitConverter.ToInt32(b, 0);
            b = new byte[data.Size];
            file.Read(b, 0, data.Size);
            data.Data = b;
            data.Handle = System.Runtime.InteropServices.GCHandle.Alloc(data.Data, System.Runtime.InteropServices.GCHandleType.Pinned);
            return data;
        }
        public static void ReadChannelData(Stream file, FMTChunk fmt, out DATAChunk[] channels)
        {
            byte[] b = new byte[4];
            file.Read(b, 0, 4);
            char[] id = Encoding.ASCII.GetChars(b);
            file.Read(b, 0, 4);
            var Size = BitConverter.ToInt32(b, 0);
            channels = new DATAChunk[fmt.NumChannels];
            var buf = new byte[fmt.BitsPerSample / 8];
            for (int i = 0; i < fmt.NumChannels; i++)
            {
                channels[i].Data = new byte[Size / fmt.NumChannels];
                channels[i].Handle = 
                    System.Runtime.InteropServices.GCHandle.Alloc(channels[i].Data, System.Runtime.InteropServices.GCHandleType.Pinned);
                channels[i].Size = Size / fmt.NumChannels;
            }
            int index = 0;
            for (int j = 0; j < Size / fmt.NumChannels; j += 1)
            {
                if (j == 0)
                {
                    file.Read(channels[index].Data, j, fmt.BitsPerSample / 8);
                }
                file.Read(channels[index].Data, j - (1 * index), fmt.BitsPerSample / 8);
                index += 1;
                if (index == fmt.NumChannels) index = 0;
            }
            
        }
    }
}
