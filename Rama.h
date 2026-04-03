#ifndef RAMA_H
#define RAMA_H

class Rama {
private:
	int width;
	int height;
	char rama[6][7];
	bool randul_galbenului; //primul jucator e galben, celalalt e rosu
	bool joc_finalizat;

public:
	Rama(int,int);
	void realizeazaMutare(int, int);
	void reset();
	
	bool isJocFinalizat() const;
	char getCuloareLaRand() const;
	char getJeton(int, int) const;
	int getRandPreview(int) const;

private:

	void verificaStatusJoc(int, int, char);
	void afisareEroare(const char*) const;

};

#endif