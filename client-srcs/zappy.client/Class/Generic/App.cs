using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Zappy.Client.Network;

namespace Zappy.Client
{
    public enum LogLevel
    {
        INFORMATION,
        SUCCESS,
        WARNING,
        ERROR,
        FATAL
    }

    public static class App
    {
        public static NetworkEngine Network = new NetworkEngine();

        private static double GetProcessMemoryUsage()
        {
            Process currentProcess = System.Diagnostics.Process.GetCurrentProcess();
            return (currentProcess.WorkingSet64 / 1024);

        }

        public static int Log(LogLevel level, string message)
        {
            Console.WriteLine("[{0} || Mem {1} bytes]", DateTime.Now.ToString("dd/MM/yyyy - h:mm:ss tt"), GetProcessMemoryUsage());

            if (level == LogLevel.SUCCESS)
                Console.ForegroundColor = ConsoleColor.Green;
            if (level == LogLevel.WARNING)
                Console.ForegroundColor = ConsoleColor.Yellow;
            if (level == LogLevel.ERROR || level == LogLevel.FATAL)
                Console.ForegroundColor = ConsoleColor.Red;
            if (level == LogLevel.INFORMATION)
                Console.ForegroundColor = ConsoleColor.Cyan;

            Console.WriteLine("> {0} : {1}\n", level.ToString(), message);
            Console.ResetColor();


            if (level == LogLevel.FATAL)
            {
                System.Environment.Exit(-1);
                Console.Read();
            }

            return (0);
        }

        public static void PrintListString(string _string)
        {
            List<string> args = App.ParseServerAnswerToStringList(_string);
            foreach (string str in args)
                Console.WriteLine(str);
        }

        public static List<string> ParseServerAnswerToStringList(string server_anwser)
        {
            server_anwser = server_anwser.Replace('{', ' ');
            server_anwser = server_anwser.Replace('}', ' ');
            return (server_anwser.Split(',').ToList());
        }
    }
}