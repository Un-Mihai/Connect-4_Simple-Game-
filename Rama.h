#ifndef RAMA_H
#define RAMA_H

class Rama {
private:
	int width;
	int height;
	char rama[20][20];
	bool randul_galbenului; //primul jucator e galben, celalalt e rosu
	bool joc_finalizat;

public:
	Rama(int,int);
	int getJeton(int, int);
	void realizeazaMutare(int);
	bool getStatusJoc();
	int getCuloareLaRand();
	int getRandPreview(int);

private:
	
	void verificaStatusJoc(int, int, char);
	void afisareEroare(const char*) const;

};

#endif