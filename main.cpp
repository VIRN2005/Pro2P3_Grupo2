#include <CtrlLib/CtrlLib.h>
#include <cstdlib>
using namespace Upp;

struct MyApp : TopWindow {
    int r;
    int tamaño;
    int margen_circulo;
    int r_cubo;           //Volumen -> Paso 1
    double r_cubo_por_pi; //Volumen -> Paso 2
    double respuesta;     //Volumen -> Paso 3
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

    virtual void Paint(Draw& d) override {
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
        d.DrawRect(GetSize(), White());
        
        //Lineas Exteriores del Cuadro
        d.DrawLine(10, 5, size_x - 10, 5, 6, Black());// Borde Superior
        d.DrawLine(10, size_y - 10, 10, 5, 5, Black());// Borde Izquierdo
        d.DrawLine(10, size_y - 10, size_x - 10, size_y - 10, 6, Black());// Borde Inferior
        d.DrawLine(size_x - 10, size_y - 10, size_x - 10, 5, 6, Black());// Borde Derecho
        
        //Lineas Dentro del Cuadro
        d.DrawLine(10, 100, size_x - 10, 100, 6, Black());// Borde Inferior de Rotuladores
        d.DrawLine(size_x / 3 - 20, size_y - 10, size_x / 3 - 20, 8, 6, Black());// Separación entre Nombre & Figura
        d.DrawLine(size_x / 3 + size_x / 3 + 20, size_y - 10, size_x / 3 + size_x / 3 + 20, 8, 6, Black());// Separación entre Figura & Volumen
		
		//Texto de Referencias
        d.DrawText(size_x / 9, 20, "Nombre", Arial(50).Bold(), Blue);
        d.DrawText(size_x / 2 - 65, 20, "Figura", Arial(50).Bold(), Blue);
        d.DrawText(centerX - 70 + tamaño, 20, "Volumen", Arial(50).Bold(), Blue);
        
        //NOMBRE FIGURA
        //Texto Nombre (Esfera)
        d.DrawText(50, size_y / 2, "Esfera", Arial(75), Black);
        
        //CALCULO DE VOLUMEN
        //Volumen -> Paso 1
        d.DrawText(centerX - 120 + tamaño - 90, centerY - 60, "V = 4/3 * 3.14 * r^3", Arial(50), Black);
        r_cubo = r * r * r;
        
        //Volumen -> Paso 2
        d.DrawText(centerX - 90 + tamaño - 105, size_y / 2 - 20, "V = 4/3 * 3.14 * " + AsString(r_cubo), Arial(50), Black);
        r_cubo_por_pi = r_cubo * 3.14;
        String volumen1s = AsString(r_cubo);
        
        //Volumen -> Paso 3
        d.DrawText(centerX - 90 + tamaño - 60, size_y / 2 + 20, "V = 4/3 * " + AsString(roundr(r_cubo_por_pi, 4)), Arial(50), Black);
        respuesta = 1.3333 * r_cubo_por_pi;
        d.DrawText(centerX - 120 + tamaño, size_y / 2 + 60, "V = " + AsString(FormatDouble(respuesta, 3)), Arial(70).Bold(), Green);
    
		//Forma ESFERA
		d.DrawEllipse(caja, esphera, 7, Blue);
	
		//Ellipses de Circulo
		
		
		//Linea de Radio
		d.DrawText(tamaño + tamaño - 220, centerY - 50, "r = " + AsString(r), Arial(40));
        d.DrawLine(centerX, centerY, tamaño + tamaño, centerY, 7, Red());
		}

    MyApp() {
        //Nombre de la Salida
        Title("Volumen de Circulo - David Reyes, Josué Ham & Víctor Romero").Sizeable();
        int argc = CommandLine().GetCount();
        const Vector<String>& argv = CommandLine();
        
        //Validación de Entrada ARGV y ARGC
        if (argc < 1) {
            PromptOK("Ingrese el valor de 'R' en la Linea de Comandos!");
            exit(1);
        } else {
            r = atoi(argv[0]);
        }
        MaximizeBox();
        MinimizeBox();
        
        //Valor Minimo de la Caja
        Sizeable().SetMinSize(Zsz(1400, 900));
    }
};

GUI_APP_MAIN
{
    MyApp().Sizeable().Run();
}
