using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test
{
    public partial class Form2 : Form
    {
        Bitmap printscreen = null, bmp = null;
        Graphics graphics = null, gr = null;
        Form1 f = new Form1();
       // SaveFileDialog sfd = new SaveFileDialog() { Filter = "Images|*.png;*.bmp;*.jpg", DefaultExt = ".png" };

        public Form2()
        {
            InitializeComponent();
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);

            string nowTime = DateTime.Now.ToString();
            nowTime = nowTime.Replace(":", "-");
            sfd.FileName = nowTime;

            new Button { Text = "Close me", Parent = this }.Click += (o, e) => this.Close();
            this.FormBorderStyle = FormBorderStyle.None;
            TopMost = true;
            ShowInTaskbar = false;
            WindowState = FormWindowState.Maximized;
            BackgroundImage = Shoot();
        }
        private Bitmap Shoot()
        {
            bmp = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height);
            using (gr = Graphics.FromImage(bmp))
                gr.CopyFromScreen(0, 0, 0, 0, new Size(bmp.Width, bmp.Height));
            gr = null;
            return bmp;
        }

        private Rectangle SelectedRectangle;

        protected override void OnMouseDown(MouseEventArgs e)
        {
            SelectedRectangle.Location = e.Location;
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            if (SelectedRectangle.Width > 0 && SelectedRectangle.Height > 0)
            {
                SaveSelectedRectangle();
                SelectedRectangle.Size = Size.Empty;
                Invalidate();
            }
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            var newSize = new Size(e.X - SelectedRectangle.Left, e.Y - SelectedRectangle.Top);

            if (MouseButtons == MouseButtons.Left)
                if (newSize.Width > 5 && newSize.Height > 5)
                {
                    SelectedRectangle.Size = newSize;
                    Invalidate();
                }
        }

        private void SaveSelectedRectangle()
        {
            //var sfd = new SaveFileDialog() { Filter = "Images|*.png;*.bmp;*.jpg", DefaultExt = ".png" };

            if (f.checkBox())
            {
                using (bmp = new Bitmap(SelectedRectangle.Width, SelectedRectangle.Height))
                using (gr = Graphics.FromImage(bmp))
                {
                    gr.DrawImage(BackgroundImage, -SelectedRectangle.Left, -SelectedRectangle.Top);
                    Clipboard.SetImage(bmp);
                }
                gr = null;
                bmp = null;
                this.Close();
            }
            else if (sfd.ShowDialog() == DialogResult.OK)
            {
                using (bmp = new Bitmap(SelectedRectangle.Width, SelectedRectangle.Height))
                using (gr = Graphics.FromImage(bmp))
                {
                    gr.DrawImage(BackgroundImage, -SelectedRectangle.Left, -SelectedRectangle.Top);
                    bmp.Save(sfd.FileName);
                }
                gr = null;
                bmp = null;
                this.Close();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            var r = new Region(ClientRectangle);
            r.Exclude(SelectedRectangle);
            using (var brush = new SolidBrush(Color.FromArgb(200, 0, 0, 0)))
                e.Graphics.FillRegion(brush, r);
        }

        public void fullScreen()
        {
            printscreen = new Bitmap(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height);
            graphics = Graphics.FromImage(printscreen as Image);
            graphics.CopyFromScreen(0, 0, 0, 0, printscreen.Size);

            if (f.checkBox())
                Clipboard.SetImage(bmp);
            else if (sfd.ShowDialog() == DialogResult.OK)
                using (gr = Graphics.FromImage(printscreen))
                {
                    printscreen.Save(sfd.FileName);
                }
            printscreen = null;
            graphics = null;
            gr = null;
        }
    }
}
