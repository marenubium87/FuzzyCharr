class Feline {
public:
	Feline();

	//virtual keyword allows this fcn to be overridden
	virtual void speak(void); // Feline speaks.
	bool checkHunger(void);

	//pure virtual fcn
	//by defn, Feline is an abstract class as it now contains a pure virtual fcn
	virtual void hunt(void) = 0;

protected:
	double size;
	double weight;
private:
	//things here become hidden in derived classes
};

class Lion : public Feline {
public:
	//overrides Feline : speak()
	void speak(void);	// Lion roars.

	void hunt(void);	//Lions hunt in packs.

	//pure virtual fcn -> Lion is abstract class now by defn
	virtual void huntInPack(void) = 0;
protected:
private:
};

class AfricanLion : public Lion {

};