using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using HBH.Audio.OpenAL;

namespace OpenAL
{
    class Program
    {
        static void Main(string[] args)
        {
            #region Test1
            Device d = Device.OpenDevice(string.Empty);
            Context c = new Context(d, new ContextAttributes[3] { ContextAttributes.Frequancy , ContextAttributes.Refresh , ContextAttributes.Sync }
            , new int[3] { 44100 , 60 , 1 });
            c.MakeContextCurrent();
            Console.WriteLine(Device.GetAllDevicesNames()[0]);
            Source[] srcs = new Source[0];
            Source.GenerateSources(2, ref srcs);
            HBH.Audio.OpenAL.Buffer[] bufs = new HBH.Audio.OpenAL.Buffer[0];
            HBH.Audio.OpenAL.Buffer.GenerateBuffers(2, ref bufs);
            System.IO.FileStream fs = System.IO.File.Open("Something.wav", System.IO.FileMode.Open);
            var r = HBH.Audio.IO.Wave.ReadRiff(fs);
            Console.WriteLine(r.Size);
            var fmt = HBH.Audio.IO.Wave.ReadFMT(fs);
            Console.WriteLine(fmt.Size);
            Console.WriteLine(Listener.Position.ToString());
            HBH.Audio.IO.Wave.DATAChunk[] ds;
            HBH.Audio.IO.Wave.ReadChannelData(fs, fmt, out ds);
            bufs[0].FillData(BufferFormats.Mono16, ds[0].DataToPtr(), ds[0].Size, fmt.SampleRate);
            bufs[1].FillData(BufferFormats.Mono16, ds[1].DataToPtr(), ds[1].Size, fmt.SampleRate);
            srcs[0].AttachBuffer(bufs[0]);
            srcs[1].AttachBuffer(bufs[1]);
            srcs[0].MaxDistance = 10;
            srcs[1].MaxDistance = 10;
            Console.WriteLine(srcs[0].MaxDistance);
            Source.PlayAsync(2, srcs);
            Thread.Sleep(1000 * 3);
            Console.WriteLine("Phase 2");
            srcs[0].Position = new Vector(5, 0, 0); 
            srcs[1].Position = new Vector(-5, 0, 0);
            while (srcs[0].SourceState == SourceState.Playing) ;
            c.Dispose();
            Console.ReadLine();
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

        public BufferFormats GetBufferFormats(HBH.Audio.IO.Wave.FMTChunk fmt)
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

