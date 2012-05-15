using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;

namespace Core3Folders
{
    class Core3Folders
    {
        static void Recurse(StringWriter writer, string dir, int level)
        {
            string[] parts = dir.Split('\\');
            string tabs = new string('\t', level);

            writer.Write(tabs + "<Filter\r\n");

            string name = parts[parts.Length - 1];

            name = name[0].ToString().ToUpper() + name.Substring(1);

            writer.Write(tabs + "\tName=\"" + name + "\"\r\n");
            writer.Write(tabs + "\t>\r\n");
            string[] dirs = Directory.GetDirectories(dir);

            foreach (string d in dirs)
            {
                if (!d.Contains(".svn"))
                    Recurse(writer, d, level + 1);
            }
            string[] files = Directory.GetFiles(dir);

            foreach (string file in files)
            {
                if (file.Contains(".cpp") || file.Contains(".h") || file.Contains(".idl"))
                {
                    writer.Write(tabs + "\t<File\r\n");
                    writer.Write("RelativePath=\"..\\..\\..\\" + file + "\"\r\n");
                    writer.Write(tabs + "\t\t>\r\n");
                    writer.Write(tabs + "\t</File>\r\n");
                }
            }
            writer.Write(tabs + "</Filter>\r\n");
        }

        static void Main(string[] args)
        {

            StringWriter writer = new StringWriter();

            string projFile = "SWGEmu2005.vcproj";

            if (!File.Exists(projFile))
            {
                Console.Write("Project file: " + projFile + " not found. Run from the build/win32/SWGEmu2005 directory.\n");
                return;
            }

            string projFileContents;

            try
            {
                projFileContents = File.ReadAllText(projFile);
            }
            catch (IOException e)
            {
                Console.Write("Error reading project file: " + e.Message);
                return;
            }

            Console.Write(Directory.GetCurrentDirectory() + "\n");

            Directory.SetCurrentDirectory("../../../");

            Console.Write(Directory.GetCurrentDirectory() + "\n");

            Recurse(writer, "src", 2);
            //Recurse(writer, "../MMOEngine/include", 2);

            Directory.SetCurrentDirectory("build/win32/SWGEmu2005");

            Regex regex1 = new Regex("<Filter.+</Filter>", RegexOptions.Singleline);
            Regex regex2 = new Regex("<Filter.+?>", RegexOptions.Singleline);

            // keep the generated data in filesPortion
            string filesPortion = writer.ToString();
            string rootFolderItem;


            // save the extra arguments to the Sources file directory
            Match match = regex2.Match(projFileContents);

            if (!match.Success)
            {
                Console.Write("No folders in project.\n");
                return;
            }
            rootFolderItem = match.Groups[0].Value.ToString();

            // and replace the parsed sources dir in the patch string
            filesPortion = regex2.Replace(filesPortion, rootFolderItem,1);

            try
            {
                if (File.Exists(projFile + ".bak"))
                    File.Delete(projFile + ".bak");

                File.WriteAllText(projFile + ".bak", projFileContents);
            }
            catch (IOException e)
            {
                Console.Write("Failed to save backup project file: " + projFile + ".bak\n");
                return;
            }

            // patch the project file
            string newProjFile = regex1.Replace(projFileContents, filesPortion,1);

            try
            {
                File.Delete(projFile);
            }
            catch(Exception)
            {
                Console.Write("Failed to delete original project file.  Please close your project and/or make sure you have write permissions to that file.\n");
                return;
            }

            try
            {
                File.WriteAllText(projFile, newProjFile);
            }
            catch(Exception)
            {
                Console.Write("Failed to replace original project file.\n");
                return;
            }
            Console.Write("File successfully patched.\n");
        }
    }
}
