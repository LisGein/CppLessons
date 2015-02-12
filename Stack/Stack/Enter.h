

class Enter{
public:
	//установка массива
	void cin(int enter_mass[]){
		
		for (int i = 1; i < 11; i++){
			mass[i] = enter_mass[i];
		}
	}
private:
	int mass[10];
};