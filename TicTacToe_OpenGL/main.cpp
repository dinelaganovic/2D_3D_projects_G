#include <windows.h>
#include <GL/glut.h> // glut (gl utility toolkit) basic windows functions, keyboard, mouse.
#include <stdio.h>   // standard (I/O library)
#include <stdlib.h>  // standard library (set of standard C functions
#include <math.h>    // Math library (Higher math functions )
#include <string.h>
// Svetla
GLfloat LightAmbient[] = {4.0, 0.0, 0.0};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {0.0, 1.0, 0.0, 1.0};
GLfloat LightSpecular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_diffuse[]={0.1, 0.1, 0.3, 1.0};
GLfloat mat_ambient[]={0.1, 0.2, 0.1, 1.0};
GLfloat mat_shininess = 5.0;
int abc = 0;
GLuint texture;
GLuint texture1;
GLuint texture2;
GLuint texture3;

//Funkcija za iscrtavanje texture
GLuint LoadTexture(const char* filename, int width, int height){
       GLuint texture;
       unsigned char* data;
       FILE* file;
       file=fopen(filename, "rb");
       if(file==NULL)return 0;
       data=(unsigned char*)malloc(width * height * 3);
       fread(data,width * height * 3,1,file);
       fclose(file);
       glGenTextures(1,&texture);
       glBindTexture(GL_TEXTURE_2D,texture);
       glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
       glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
       free(data);
       return texture;
}


// Win = windows size, mouse = mouse position
int mouse_x, mouse_y, Win_x, Win_y, object_select;
int spin, spinboxes;
// Win = 1 igrac pobedio, -1 computer pobedio, 2 nereseno.
// irač or computer; 1 = X, -1 = O
int player, computer, win, start_game;
// Imamo 8 mogućnostu, 3 kolone, 3 reda i 2 dijagonale
//
// 0 | 1 | 2
// 3 | 4 | 5
// 6 | 7 | 8
//
// row, column, diagonal informacije
static int box[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
// nasa tabla matrica
// 1 = X, -1 = O, 0 = prazno mesto
int box_map[9];
//moguće lokacije za nase vrednosti
int object_map[9][2] = {{-6, 6}, {0, 6}, {6, 6}, {-6, 0}, {0, 0}, {6, 0}, {-6, -6}, {0, -6}, {6, -6}}; // pokazivac za X
GLUquadricObj *Cylinder;
// pocetak igrea
void init_game(void)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        box_map[i] = 0;
    }
    win = 0;
    start_game = 1;
}

int check_move(void)
{
    int i, t = 0;
   // proveravanje 3 polja
    for (i = 0; i < 8; i++)
    {
        t = box_map[box[i][0]] + box_map[box[i][1]] + box_map[box[i][2]];
        if ((t == 3) || (t == -3))
        {
            spinboxes = i;
            return (1);
        }
    }
    t = 0;
    // provera kad je nerešeno
    for (i = 0; i < 8; i++)
    {
        t = t + abs(box_map[box[i][0]]) + abs(box_map[box[i][1]]) + abs(box_map[box[i][2]]);
    }
    if (t == 24)
        return (2);
    return (0);
}
// Provera da li treba da blokiramo drugog igraca
int blocking_win(void)
{
    int i, t;
    for (i = 0; i < 8; i++)
    {
        t = box_map[box[i][0]] + box_map[box[i][1]] + box_map[box[i][2]];
        if ((t == 2) || (t == -2))
        {
            // Ako je prazno proveri
            if (box_map[box[i][0]] == 0)
                box_map[box[i][0]] = computer;
            if (box_map[box[i][1]] == 0)
                box_map[box[i][1]] = computer;
            if (box_map[box[i][2]] == 0)
                box_map[box[i][2]] = computer;
            return (1);
        }
    }
    return (0);
}
// provera slobodnog polja u čoskovima table
int check_corner(void)
{
    int i;
    if (box_map[0] == 0)
    {
        box_map[0] = computer;
        i = 1;
        return (1);
    }
    if (box_map[2] == 0)
    {
        box_map[2] = computer;
        i = 1;
        return (1);
    }
    if (box_map[6] == 0)
    {
        box_map[6] = computer;
        i = 1;
        return (1);
    }
    if (box_map[8] == 0)
    {
        box_map[8] = computer;
        i = 1;
        return (1);
    }
    return (0);
} //proveri slobodno mesto u redu
int check_row(void)
{
    if (box_map[4] == 0)
    {
        box_map[4] = computer;
        return (1);
    }
    if (box_map[1] == 0)
    {
        box_map[1] = computer;
        return (1);
    }
    if (box_map[3] == 0)
    {
        box_map[3] = computer;
        return (1);
    }
    if (box_map[5] == 0)
    {
        box_map[5] = computer;
        return (1);
    }
    if (box_map[7] == 0)
    {
        box_map[7] = computer;
        return (1);
    }
    return (0);
}
// potez kompjutera
int computer_move()
{
    if (blocking_win() == 1)
        return (1);
    if (check_row() == 1)
        return (1);
    if (check_corner() == 1)
        return (1);
    return (0);
}
//ispis teksta na ekranu
void Sprint(int x, int y, char *st)
{
    int l, i;
    l = strlen(st);
    glRasterPos2i( x, y); // lokacija za ispis teksta
    for (i = 0; i < l; i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }
}
void SPrint(int x, int y, char *st)
{
    int l, i;
    l = strlen(st);
    glRasterPos2i( x, y);
    for (i = 0; i < l; i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }
}
// funkcija za rotaciju oblika - ako je preko 360 stepeni rotacija presla kreci od nule
static void TimeEvent(int te)
{
    spin++; //
    if (spin > 360)
        spin = 180;
    glutPostRedisplay();
    glutTimerFunc(8, TimeEvent, 1); // resetovanje tajmera
}
// pocetni ekran
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    // dodavanje svetla
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING); // paljenje svetla
    glEnable(GL_LIGHT1);   // paljenje prvog svetla
    start_game = 0;
    win = 0;
    // kreiranje objekta
    Cylinder = gluNewQuadric();
    gluQuadricDrawStyle(Cylinder, GLU_FILL);
    gluQuadricNormals(Cylinder, GLU_SMOOTH);
    gluQuadricOrientation(Cylinder, GLU_OUTSIDE);
}
void Draw_O(int x, int y, int z, int a)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(a, 1, 0, 0);
    glutSolidTorus(0.3, 1.0, 10, 300);
    glPopMatrix();
}
void Draw_X(int x, int y, int z, int a)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glPushMatrix();
    glRotatef(a, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 1, 0, 0);
    glTranslatef(0, 0, -2);
    gluCylinder(Cylinder, 0.3, 0.3, 4, 10, 16);
    glPopMatrix();
    glPushMatrix();
    glRotatef(a, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(315, 1, 0, 0);
    glTranslatef(0, 0, -2);
    gluCylinder(Cylinder, 0.3, 0.3, 4, 10, 16);
    gluCylinder(Cylinder, 0.3, 0.3, 4, 10, 16);
    glPopMatrix();
    glPopMatrix();
}

void display(void)
{
    //////
      if (abc == 3)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);//Pokrenuti texture
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,texture);
        glBegin(GL_POLYGON);
         glTexCoord2d(0.0, 16.0); glVertex2f(-10.5,14.0);//leva prva
         glTexCoord2d(10.0, 11.0); glVertex2f(5.5,-0.5);
         glTexCoord2d(-6.0, 77.0); glVertex2f(21.5,0.5);//desna 3 tacka
         glTexCoord2d(22.0, 2.0); glVertex2f(8.5,11.5);//tacka 2
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glMatrixMode(GL_PROJECTION);              // rad u matrici
        glLoadIdentity();
        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0); // Ortho izgled
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
        glColor3f(0.9, 0.8, 0.7);
        Sprint(-7, 5, "OpenGL project");
        glColor3f(0.1, 0.2, 0.3);
        Sprint(-7, 4, "Tic Tac Toe ");
        glColor3f(0.9, 0.8, 0.7);
        Sprint(-7, 2, "Overview");
        glColor3f(0.1, 0.2, 0.3);
        SPrint(-7, 1, "Tic Tac Toe is a two-player game where the first player to");
        SPrint(-7, 0,  "connect a line of pieces from one side or corner of the board.");
        glColor3f(0.9, 0.8, 0.7);
        Sprint(-7, -2, "Rules");
        glColor3f(0.1, 0.2, 0.3);
        SPrint(-7, -3, "1.X moves first.");
        SPrint(-7, -4, "2.A piece may be placed on any empty space.");
        SPrint(-7, -5, "3.A player wins by being the first to connect a line of friendly");
        SPrint(-7, -6, "  pieces from one side or corner of the board to the other.");
        SPrint(-7, -7, "4.The game ends when either one player wins or it is no longer possible");
        SPrint(-7, -8, "  for a player to win (in which case the result is a draw).");
        glutSwapBuffers();
    }
    else if (abc == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);//Pokrenuti texture
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,texture);
        glBegin(GL_POLYGON);
         glTexCoord2d(0.0, 16.0); glVertex2f(-10.5,14.0);//leva prva
         glTexCoord2d(0.0, 1.0); glVertex2f(-0.5,-0.5);
         glTexCoord2d(-6.0, 77.0); glVertex2f(21.5,0.5);//desna 3 tacka
         glTexCoord2d(22.0, 2.0); glVertex2f(8.5,11.5);//tacka 2
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
        glColor3f(0.9, 0.8, 0.7);
        Sprint(-6, 0, "OpenGL project game ");
        glColor3f(0.1, 0.2, 0.3);
        Sprint(-6, -1, "Tic Tac Toe ");
        glColor3f(0.8, 0.2, 0.3);
        Sprint(-6, -3, "Right Click for Menu for all information ");
        glutSwapBuffers();
    }
    else
    {
        //char txt[30];
        int ix, iy;
        int i;
        int j;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_LIGHTING);
        glColor3f(0.9, 0.8, 0.7);
        if (win == 1)
            Sprint(-2, 8, "Congratulations! You Won");
        if (win == -1)
            Sprint(-2, 8, "Computer Won");
        if (win == 2)
            Sprint(-2, 8, "Draw");
        glColor3f(0.0, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 1, 30);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();



        glEnable(GL_LIGHTING);
//kameraa
        gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
        // Draw Grid
        for (ix = 0; ix < 4; ix++)
        {
            glPushMatrix();
            glColor3f(1, 1, 1);
            glBegin(GL_LINES);
            glVertex2i(-9, -9 + ix * 6);
            glVertex2i(9, -9 + ix * 6);
            glEnd();
            glPopMatrix();
        }
        for (iy = 0; iy < 4; iy++)
        {
            glPushMatrix();
            glColor3f(1, 1, 1);
            glBegin(GL_LINES);
            glVertex2i(-9 + iy * 6, 9);
            glVertex2i(-9 + iy * 6, -9);
            glEnd();
            glPopMatrix();
        }
        for (i = 0; i < 9; i++)
        {
            j = 0;
            if (abs(win) == 1)
            {
                if ((i == box[spinboxes][0]) || (i == box[spinboxes][1]) || (i == box[spinboxes][2]))
                {
                    j = spin;
                }
                else
                    j = 0;
            }
            if (box_map[i] == 1)
            {
                Draw_O(object_map[i][0], object_map[i][1], -1, j);
            }
            if (box_map[i] == -1)
            {
                Draw_X(object_map[i][0], object_map[i][1], -1, j);
            }
        }
        glutSwapBuffers();
    }
}
// This is called when the window has been resized.
void reshape(int w, int h)
{
    Win_x = w;
    Win_y = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
} // Read the keyboard
void keyboard(unsigned char key, int x, int y)
{
    if (key == '1') {
       exit(0);
    }
    if (key == '2') {
        glEnable(GL_LIGHT1);
    }
    if (key == '3') {
        glDisable(GL_LIGHT1);
    }
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{

    mouse_x = (18 * (float)((float)x / (float)Win_x)) / 6;
    mouse_y = (18 * (float)((float)y / (float)Win_y)) / 6;
    // pozicija klika u kom polju je kliknuto
    object_select = mouse_x + mouse_y * 3;
    if (start_game == 0)
    {
        if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
        {
            player = 1;
            computer = -1;
            init_game();
            computer_move();
            return;
        }
        if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        {
            player = -1;
            computer = 1;
            init_game();
            return;
        }
    }
    if (start_game == 1)
    {
        if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        {
            if (win == 0)
            {
                if (box_map[object_select] == 0)
                {
                    box_map[object_select] = player;
                    win = check_move();
                    if (win == 1)
                    {
                        start_game = 0;
                        return;
                    }

                    computer_move();
                    win = check_move();
                    if (win == 1)
                    {
                        win = -1;
                        start_game = 0;
                    }
                }
            }
        }
    }
    if (win == 2)
        start_game = 0;
}
void menu(int choice)
{
    switch (choice)
    {
    case 1:
        abc = 1;
        glutMouseFunc(mouse);
        break;
    case 2:
        abc = 3;
        glutMouseFunc(mouse);
        break;
    case 3:
        exit(0);
        break;
    }
}

// Main program
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(850, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("Tic Tac Toe");
    init();
    glutCreateMenu(menu);
    glutAddMenuEntry("Start game", 1);
    glutAddMenuEntry("Help", 2);
    glutAddMenuEntry("Quit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    glutTimerFunc(50, TimeEvent, 1);
//teksture
    texture=LoadTexture("./textures/texture2.raw",256, 256);
    texture1=LoadTexture("./textures/texture3.raw",256, 256);
    texture2=LoadTexture("./textures/texture.raw",256, 256);
    texture3=LoadTexture("./textures/texture1.raw",256, 256);
    glutMainLoop();
    return 0;
}
