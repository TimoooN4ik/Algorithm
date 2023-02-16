using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using Microsoft.Win32;

namespace Test
{
    public partial class Form1 : Form
    {
        Form2 f;
        static bool d = true;
        const string StartName = "autoload";
        public Form1()
        {
            InitializeComponent();

            //AutoloadProgam();
            int count = 0;
            foreach (Process pr in Process.GetProcesses())
                if (pr.ProcessName == this.ProductName)
                    count++;

            if (count > 1)
                Process.GetCurrentProcess().Kill();

            notifyIcon1.Visible = false;
            this.notifyIcon1.MouseDoubleClick += new MouseEventHandler(notifyIcon1_MouseDoubleClick);
            this.Resize += new System.EventHandler(this.Form1_Resize);

            notifyIcon1.ContextMenuStrip = contextMenuStrip1;

            //WindowState = FormWindowState.Minimized;
            //Hide();
        }

        public bool AutoloadProgam()
        {
            string ExePath = System.Windows.Forms.Application.ExecutablePath;
            RegistryKey reg;
            reg = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\");
            try
            {
                reg.SetValue(StartName, ExePath);
                reg.Close();
            }
            catch
            {
                return false;
            }
            return true;
        }
        private void Form1_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
            {
                Hide();
                notifyIcon1.Visible = true;
            }
        }
        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
            notifyIcon1.Visible = false;
            WindowState = FormWindowState.Normal;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            f = new Form2();
            f.Show();
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Show();
            notifyIcon1.Visible = false;
            WindowState = FormWindowState.Normal;
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        public bool checkBox()
        {
            if (d)
            {
                //MessageBox.Show("d");
                return true;
            }
            return false;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            d = !d;
        }
    }
}
