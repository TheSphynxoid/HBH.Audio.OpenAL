using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using HBH.Audio.OpenAL;
using System.Collections.Concurrent;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace OpenAL
{
    class Program
    {
        static void Main(string[] args)
        {
            #region Test1
            //Console.WriteLine(".Wav File Path");
            //Console.ReadLine();
            System.IO.FileStream fs = System.IO.File.Open("Something.wav", System.IO.FileMode.Open);
            var r = HBH.Audio.IO.Wave.ReadRiff(fs);
            Console.WriteLine("File Size : " + r.Size + " Bytes");
            var fmt = HBH.Audio.IO.Wave.ReadFMT(fs);
            Device device = Device.OpenDevice(string.Empty);
            Context context = new Context(device, new ContextAttributes[1] { ContextAttributes.Refresh }, new int[1] { 60 });
            context.MakeContextCurrent();
            Source source = new Source();
            HBH.Audio.OpenAL.Buffer buffer = new HBH.Audio.OpenAL.Buffer();
            var data = HBH.Audio.IO.Wave.ReadData(fs);
            Console.WriteLine("Length : " + ((float)data.Size) / fmt.ByteRate / 60);
            buffer.FillData(GetBufferFormats(fmt), data.DataToPtr(), data.Size, fmt.SampleRate);
            source.AttachBuffer(buffer);
            source.PlayAsync();
            Console.WriteLine("Done");
            Console.Read();
            #endregion
            #region test2
            //Device d = Device.OpenCaptureDevice(null, 44100, BufferFormats.Mono16, 882000);
            //Console.WriteLine("Capture Statrted");
            //d.CaptureStart();
            //Thread.Sleep(1000 * 5);
            //Console.WriteLine("Capture Stopped");
            //int s = d.GetAvailableSamples();
            //while (s < 882000 / 2)
            //{
            //    s = d.GetAvailableSamples();
            //}
            //IntPtr dataptr = new IntPtr();
            //d.CaptureSamples(ref dataptr, 882000 / 2);
            //byte[] data = new byte[882000];
            //System.Runtime.InteropServices.Marshal.Copy(dataptr, data, 0, 882000);
            //Console.WriteLine("Samples Captured");
            //d.CaptureStop();
            //d.Dispose();
            //HBH.Audio.IO.Wave.FMTChunk fmt = new HBH.Audio.IO.Wave.FMTChunk();
            //fmt.ID = "fmt ".ToCharArray();
            //fmt.Size = 16;
            //fmt.AudioFormat = 1;
            //fmt.NumChannels = 1;
            //fmt.SampleRate = 44100;
            //fmt.BlockAlign = 4;
            //fmt.BitsPerSample = 16;
            //fmt.ByteRate = fmt.SampleRate * fmt.BlockAlign;
            //System.IO.FileStream stream = (System.IO.FileStream)HBH.Audio.IO.Wave.CreateNewWaveFile("Capture.wav", data, fmt);
            //Console.WriteLine(stream.Name);
            //Console.WriteLine("Done!");
            //Console.WriteLine("Press enter to exit.");
            //Console.ReadLine();
            #endregion
        }
        public static BufferFormats GetBufferFormats(HBH.Audio.IO.Wave.FMTChunk fmt)
        {
            if (fmt.NumChannels == 1)
            {
                if (fmt.BitsPerSample == 8)
                {
                    return BufferFormats.Mono8;
                }
                else
                {
                    return BufferFormats.Mono16;
                }
            }
            else
            {
                if (fmt.BitsPerSample == 8)
                {
                    return BufferFormats.Stereo8;
                }
                else
                {
                    return BufferFormats.Stereo16;
                }
            }
        }
    }
}

