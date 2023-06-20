#include <CtrlLib/CtrlLib.h>
#include <cstdlib>
using namespace Upp;

struct MyApp : TopWindow {
    int a;
    int tamaño;
    int margen_circulo;
    int r_cubo;           //Volumen -> Paso 1
    double r_cubo_por_pi; //Volumen -> Paso 2
    int respuesta;        //Volumen -> Paso 3
    int size_y;
    int size_x;
    int centerX;
    int centerY;
    int radio_circulo;
    int desplazamiento;
    Pointf centro;
    Pointf centro2;
    Pointf centro3;
    Rect caja;
    Rect caja2;
    Rect caja3;
    Color esphera;

    virtual void Paint(Draw& w) override {
        //Calcular Values
        tamaño = GetSize().cx / 3;
        margen_circulo = 10;
        size_y = GetSize().cy;
        size_x = GetSize().cx;
        centerX = GetSize().cx / 2;
        centerY = GetSize().cy / 2;
        radio_circulo = tamaño / 2;
        desplazamiento = 250;

        centro = Pointf(centerX - radio_circulo, centerY - radio_circulo);
        caja = Rect(Point(centro), Size(tamaño, tamaño));
        centro2 = Pointf(centerX - radio_circulo, (centerY - radio_circulo) + (desplazamiento / 2));
        caja2 = Rect(Point(centro2), Size(tamaño, tamaño - desplazamiento));
        centro3 = Pointf((centerX - radio_circulo) + (desplazamiento / 2), centerY - radio_circulo);
        caja3 = Rect(Point(centro3), Size(tamaño - desplazamiento, tamaño));
        esphera = Color(235, 175, 153);

        //Fondo Blanco
        w.DrawRect(GetSize(), White());
        
        //Lineas Exteriores del Cuadro
        w.DrawLine(10, 5, size_x - 10, 5, 6, Black());// Borde Superior
        w.DrawLine(10, size_y - 10, 10, 5, 5, Black());// Borde Izquierdo
        w.DrawLine(10, size_y - 10, size_x - 10, size_y - 10, 6, Black());// Borde Inferior
        w.DrawLine(size_x - 10, size_y - 10, size_x - 10, 5, 6, Black());// Borde Derecho
        
        //Lineas Dentro del Cuadro
        w.DrawLine(10, 100, size_x - 10, 100, 6, Black());// Borde Inferior de Rotuladores
        w.DrawLine(size_x / 3 - 20, size_y - 10, size_x / 3 - 20, 8, 6, Black());// Separación entre Nombre & Figura
        w.DrawLine(size_x / 3 + size_x / 3 + 20, size_y - 10, size_x / 3 + size_x / 3 + 20, 8, 6, Black());// Separación entre Figura & Volumen
		
		//Texto de Referencias
        w.DrawText(size_x / 9, 20, "Nombre", Arial(50).Bold(), Blue);
        w.DrawText(size_x / 2 - 65, 20, "Figura", Arial(50).Bold(), Blue);
        w.DrawText(centerX - 70 + tamaño, 20, "Volumen", Arial(50).Bold(), Blue);
        
        //NOMBRE FIGURA
        //Texto Nombre (Esfera)
        w.DrawText(50, size_y / 2, "Esfera", Arial(75).Bold(), Black);
        
        //CALCULO DE VOLUMEN
        //Volumen -> Paso 1
        w.DrawText(centerX - 90 + tamaño - 90, centerY - 60, "V = 4/3 * 3.14 * r^3", Arial(50), Black);
        r_cubo = a * a * a;
        
        //Volumen -> Paso 2
        w.DrawText(centerX - 90 + tamaño - 105, size_y / 2 - 20, "V = 4/3 * 3.14 * " + AsString(r_cubo), Arial(50), Black);
        r_cubo_por_pi = r_cubo * 3.14;
        String volumen1s = AsString(r_cubo);
        
        //Volumen -> Paso 3
        w.DrawText(centerX - 90 + tamaño - 60, size_y / 2 + 20, "V = 4/3 * " + AsString(roundr(r_cubo_por_pi, 4)), Arial(50), Black);
        respuesta = 1.3333 * r_cubo_por_pi;
        w.DrawText(centerX - 90 + tamaño, size_y / 2 + 60, "V = " + AsString(respuesta), Arial(70).Bold(), Green);
    }

    MyApp() {
        Title("Volumen de Circulo - David Reyes, Josué Ham & Víctor Romero").Sizeable();
        int argc = CommandLine().GetCount();
        const Vector<String>& argv = CommandLine();
        if (argc < 1) {
            PromptOK("Ingrese el valor de 'R'");
            exit(1);
        } else {
            a = atoi(argv[0]);
        }
        MaximizeBox();
        MinimizeBox();
        Sizeable().SetMinSize(Zsz(1400, 900));
    }
};

GUI_APP_MAIN
{
    MyApp().Sizeable().Run();
}
