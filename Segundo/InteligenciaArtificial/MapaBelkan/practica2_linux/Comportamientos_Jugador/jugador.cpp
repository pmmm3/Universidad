#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>

// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {
	Action sigAccion = actIDLE;
	
	if (col_obj != sensores.destinoC || fil_obj != sensores.destinoF)
	{
		col_obj = sensores.destinoC;
		fil_obj = sensores.destinoF;
		hayplan = false;
	}
	if (!hayplan)
	{
		actual.fila        = sensores.posF;
		actual.columna     = sensores.posC;
		actual.orientacion = sensores.sentido;
		destino.fila       = sensores.destinoF;
		destino.columna    = sensores.destinoC;	

		if (sensores.nivel ==4) // Mostramos por primera vez la primera vision
			vistamapa1(sensores);
		ultima_orientacion=sensores.sentido;
		hayplan = pathFinding (sensores.nivel, actual, destino, plan);
	}
	if (hayplan && plan.size()>0)
	{
		if (ultima_orientacion != sensores.sentido){
			vistamapa1(sensores);
			ultima_orientacion=sensores.sentido;
		}
		else
			vistamapa2(sensores);
		
		
		
		sigAccion = plan.front();
		plan.erase(plan.begin());
	}
	else
	{
		
		sigAccion = actIDLE;
	}
	
	

  return sigAccion;
}

//Funcion que segun la orientacion revela el mapa al inicio
void ComportamientoJugador::vistamapa1(Sensores sensores)
{
int t = 0;
	switch (sensores.sentido)
	{
		case norte:
			for (int i = sensores.posF; i > sensores.posF -4 && i > 0 ;i--)
			{
				for (int j= sensores.posC - (sensores.posF-i) ; j <  sensores.posC + (sensores.posF-i+1) && sensores.posC <99 && sensores.posC>0; j++)
				{
					mapaResultado[i][j]=sensores.terreno[t];
					t++;
						
				}
			}
				
			break;
		case este:
			for (int j = sensores.posC; j < sensores.posC + 4 ; j++)
			{
				for (int i = sensores.posF-(j-sensores.posC);i < sensores.posF+(j-sensores.posC)+1 && i <= 99 && i >=0; i++)
				{
					mapaResultado[i][j] = sensores.terreno[t];
					t++;
				}  
			}
			break;
		case sur:
			for(int i = sensores.posF; i < sensores.posF + 4 && i<99;i++)
			{
				for (int j= sensores.posC + (i-sensores.posF+1) ; j > sensores.posC - (i-sensores.posF) && sensores.posC <99 && sensores.posC>0; j--)
				{
					mapaResultado[i][j-1]=sensores.terreno[t];
					t++;	
				}	
			}
			break;
		case oeste:
			for (int j = sensores.posC; j > sensores.posC -4 && j >= 0 ;j--)
			{
				for(int i = sensores.posF + (sensores.posC - j); i >= sensores.posF - (sensores.posC - j) && i <99 && i>=0; i--)
				{
					mapaResultado[i][j]=sensores.terreno[t];
					t++;
				}
			}
		break;
		default:
			break;
		}
}
//Funcion que en cada paso pinta la nueva zona descubierta
void ComportamientoJugador::vistamapa2(Sensores sensores)
{
	int t=9;
	switch (sensores.sentido)
	{	
	case norte :
		if(sensores.posF - 3 >=0)
		{
			for(int j = sensores.posC-3;j < sensores.posC+4 && j >=0 && j<=99;j++)
			{
				mapaResultado[sensores.posF-3][j]=sensores.terreno[t];
				t++;
			}
		}
		break;
	case sur :
		if(sensores.posF + 3 <=99)
		{
			for(int j = sensores.posC+3;j >= sensores.posC-3 && j >=0 && j<=99;j--)
			{
				mapaResultado[sensores.posF+3][j]=sensores.terreno[t];
				t++;
			}
		}
		break;
	case este :
		if(sensores.posC + 3 <=99)
		{
			for (int i = sensores.posF -3 ; i <= sensores.posF +3; i++)
			{
				mapaResultado[i][sensores.posC+3]=sensores.terreno[t];
				t++;
			}
			
		}
		break;
	case oeste :
		if(sensores.posC - 3 >=0)
		{
			for (int i = sensores.posF +3 ; i >= sensores.posF -3; i--)
			{
				mapaResultado[i][sensores.posC-3]=sensores.terreno[t];
				t++;
			}
			
		}
		break;

	default:
		break;
	}
}
// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			return pathFinding_Profundidad(origen,destino,plan);
			break;
		case 2: cout << "Busqueda en Anchura\n";
			return pathFinding_Anchura(origen,destino,plan);
			break;
		case 3: cout << "Busqueda Costo Uniforme\n";
			return	pathFinding_CostoUniforme(origen,destino,plan);
			break;
		case 4: cout << "Busqueda para el reto\n";
			return parte2(origen,destino,plan);
			break;
	}
	return false;
}



//---------------------- Implementación de la busqueda en profundidad ---------------------------

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}


// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}




struct nodo{
	estado st;
	list<Action> secuencia;
};
bool operator<(nodo const& n2, nodo const& n1)
{
	return n1.st.coste < n2.st.coste;
}
struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};


// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}
//En Anchura
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	queue<nodo> cola;											// Lista de Abiertos

  nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.front();
		}
		
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}


//Función que devuelve el coste de la casilla 

int coste(unsigned char t, bool zapatillas,bool bikini)
{
	switch (t)
	{
	case 'A':
		if (bikini)
			return 10;
		else 
			return 100;
		break;
	case 'B':
		if (zapatillas)
			return 5;
		else
			return 50;
		break;
	case 'T':
		return 2;
		break;
	default:
		return 1;
		break;
	}
}





//Con Costo Uniforme
bool ComportamientoJugador::pathFinding_CostoUniforme(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo>cola;											// Lista de Abiertos

  	nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			hijoTurnR.st.coste += coste(mapaResultado[current.st.fila][current.st.columna],current.st.zapatillas,current.st.bikini);
			
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			hijoTurnL.st.coste += coste(mapaResultado[current.st.fila][current.st.columna],current.st.zapatillas,current.st.bikini);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				hijoForward.st.coste += coste(mapaResultado[current.st.fila][current.st.columna],current.st.zapatillas,current.st.bikini);
			
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
		}
		
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}



bool ComportamientoJugador::parte2(const estado &origen, const estado &destino, list<Action>&plan)
{
	//Borro la lista
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	priority_queue<nodo>cola;											// Lista de Abiertos

  	nodo current;
	current.st = origen;
	current.secuencia.empty();

	cola.push(current);

  while (!cola.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		cola.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			hijoTurnR.st.coste += coste(mapaResultado[current.st.fila][current.st.columna],current.st.zapatillas,current.st.bikini);
			
			cola.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			hijoTurnL.st.coste += coste(mapaResultado[current.st.fila][current.st.columna],current.st.zapatillas,current.st.bikini);
			cola.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				hijoForward.st.coste += coste(mapaResultado[current.st.fila][current.st.columna],current.st.zapatillas,current.st.bikini);
			
				cola.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la cola
		if (!cola.empty()){
			current = cola.top();
		}
		
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}



// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}



void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}


// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}



int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
