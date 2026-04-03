#ifndef GENERATORMUTARI_H
#define GENERATORMUTARI_H

class GeneratorMutari {
private:
	static char culoare;
	static char culoare_inamic;
	static char copie_rama[6][7];


public:
	static void setCuloare(char);
	static void realizeazaMutare(int, char);
	static void realizeazaMutareJucator(int, int);
	static int getColoanaMutare();

	static void reset();

private:
	static int getScorMutare(int, int, bool);
	static int getEvaluareMutare();
	static int getScorLinie(int, int, int, int, char);
	static int getScorOrizontal();
	static int getScorVertical();
	static int getScorDiagonal();
	static void undoMutare(int);
};

#endif 
