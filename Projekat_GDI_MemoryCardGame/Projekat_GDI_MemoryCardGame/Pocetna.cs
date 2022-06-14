using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Projekat_GDI_MemoryCardGame
{
    public partial class Pocetna : Form
    {
        public Pocetna()
        {
            InitializeComponent();
        }

        private void p_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            Font fnt = new Font("Times New Roman", 12);
            GraphicsPath path = new GraphicsPath();
            Pen penJoin = new Pen(Color.Black, 2);
            path.StartFigure();
            path.AddLine(new Point(10, 10), new Point(130, 10));
            path.AddLine(new Point(10, 10), new Point(10, 160));
            path.AddLine(new Point(10, 160), new Point(130, 160));
            path.AddLine(new Point(130, 10), new Point(130, 160));
            penJoin.LineJoin = LineJoin.Bevel;
            g.DrawPath(penJoin, path);
            g.DrawString("Rupa", fnt, new SolidBrush(Color.Black), 43, 10);
            HatchBrush myHatchBrush =
            new HatchBrush(HatchStyle.Vertical, Color.Blue, Color.Green);
            g.FillEllipse(myHatchBrush, 43, 55, 60, 40);
            g.TranslateTransform(200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Čovek", fnt, new SolidBrush(Color.Black), 43, 10);
            GraphicsPath Person = new GraphicsPath();
            Person.AddEllipse(63, 41, 14, 14);
            Person.AddLine(58, 56, 82, 56);
            Person.AddLine(90, 80, 84, 82);
            Person.AddLine(78, 65, 77, 82);
            Person.AddLine(85, 115, 77, 115);
            Person.AddLine(70, 90, 63, 115);
            Person.AddLine(56, 115, 63, 82);
            Person.AddLine(62, 65, 56, 82);
            Person.AddLine(50, 80, 58, 56);
            g.DrawPath(Pens.Black, Person);
            g.TranslateTransform(200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Kvadar", fnt, new SolidBrush(Color.Black), 43, 10);
            HatchBrush hBrush1 = new HatchBrush(HatchStyle.DiagonalCross, Color.Black, Color.Red);
            g.FillRectangle(hBrush1, 40, 50, 60, 60);
            g.TranslateTransform(200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Trougao", fnt, new SolidBrush(Color.Black), 43, 10);
            GraphicsPath gPath = new GraphicsPath();
            Rectangle rect1 = new Rectangle(0, 0, 200, 150);
            gPath.AddRectangle(rect1);
            PathGradientBrush pathGradientBrush = new PathGradientBrush(gPath);
            pathGradientBrush.CenterColor = Color.DeepPink;
            Color[] colors = { Color.FromArgb(255, 255, 225, 225) };
            pathGradientBrush.SurroundColors = colors;
            Point p1 = new Point(70, 50);
            Point p2 = new Point(100, 115);
            Point p3 = new Point(30, 115);
            Point[] pointArray = { p1, p2, p3 };
            g.FillPolygon(pathGradientBrush, pointArray);
            g.TranslateTransform(200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Srce", fnt, new SolidBrush(Color.Black), 43, 10);
            Pen pn = new Pen(Color.Red, 2);
            Rectangle rect = new Rectangle(18, 50, 50, 50);
            g.DrawArc(pn, rect, 180, 180);
            Rectangle rect2 = new Rectangle(68, 50, 50, 50);
            g.DrawArc(pn, rect2, 180, 180);
            g.DrawLine(pn, 18, 76, 68, 130);
            g.DrawLine(pn, 118, 76, 68, 130);
            g.TranslateTransform(200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Karo", fnt, new SolidBrush(Color.Black), 43, 10);
            g.DrawLine(pn, 18, 76, 68, 110);
            g.DrawLine(pn, 118, 76, 68, 110);
            g.DrawLine(pn, 18, 76, 68, 50);
            g.DrawLine(pn, 118, 76, 68, 50);
            g.TranslateTransform(0, 200);
            g.DrawPath(penJoin, path);
            g.DrawString("Jabuka", fnt, new SolidBrush(Color.Black), 43, 10);
            Bitmap bitmap = new Bitmap(Properties.Resources.Apple);
            g.DrawImage(bitmap, 30, 40, 80,
            80);
            g.TranslateTransform(-200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Kućica", fnt, new SolidBrush(Color.Black), 43, 10);
            HatchBrush hBrush2 = new HatchBrush(HatchStyle.DashedHorizontal, Color.Green, Color.Black);
            HatchBrush hBrush3 = new HatchBrush(HatchStyle.Weave, Color.BlueViolet, Color.Blue);
            Rectangle rect5 = new Rectangle(42, 80, 50, 40);
            g.FillRectangle(hBrush3, rect5);
            Point p4 = new Point(70, 50);
            Point p5 = new Point(100, 80);
            Point p6 = new Point(30, 80);
            Point[] pointArray2 = { p4, p5, p6 };
            g.FillPolygon(hBrush2, pointArray2);
            g.TranslateTransform(-200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Pahulja", fnt, new SolidBrush(Color.Black), 43, 10);
            Pen pz = new Pen(Color.White, 3);
            g.DrawEllipse(pz, 20, 50, 90, 90);
            g.DrawLine(pz, 63, 65, 63, 130);
            g.DrawLine(pz, 28, 76, 98, 110);
            g.DrawLine(pz, 98, 66, 32, 120);
            g.TranslateTransform(-200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Smesak", fnt, new SolidBrush(Color.Black), 43, 10);
            SolidBrush br = new SolidBrush(Color.Yellow);
            SolidBrush br1 = new SolidBrush(Color.Black);
            g.FillEllipse(br, 25, 50, 80, 80);
            g.FillEllipse(br1, 40, 75, 10, 10);
            g.FillEllipse(br1, 80, 75, 10, 10);
            Rectangle rect8 = new Rectangle(40, 70, 50, 50);
            g.DrawArc(penJoin, rect8, 0, 180);
            g.TranslateTransform(-200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Tref", fnt, new SolidBrush(Color.Black), 43, 10);
            g.FillEllipse(br1, 40, 75, 50, 50);
            g.FillEllipse(br1, 60, 75, 50, 50);
            g.FillEllipse(br1, 55, 55, 40, 40);
            Rectangle rect7 = new Rectangle(70, 90, 10, 50);
            g.FillRectangle(br1, rect7);
            g.TranslateTransform(-200, 0);
            g.DrawPath(penJoin, path);
            g.DrawString("Trešnja", fnt, new SolidBrush(Color.Black), 43, 10);
            Bitmap bitmap3 = new Bitmap(Properties.Resources.cherry);
            g.DrawImage(bitmap3, 30, 40, 80,
            80);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Game_Window gm = new Game_Window();
            gm.Show();
            
        }
    }
}
