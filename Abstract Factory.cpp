// an abstract factory design pattern example, which works with the given model:
// chair               sofa
// victorian chair     victorian sofa
// modern chair        modern sofa

#include <iostream>	
#include <string>

// abstract class for chairs
class AbstractChair {
public:
	virtual ~AbstractChair() {};

	virtual std::string AssembleChair() const = 0;
};

// derived class for victorian chairs
class VictorianChair : public AbstractChair {
public:
	std::string AssembleChair() const override {
		return "You have created a victorian chair";
	}
};

// derived class for modern chairs
class ModernChair : public AbstractChair {
public:
	std::string AssembleChair() const override {
		return "You have created a modern chair";
	}
};

// abstract class for sofas
class AbstractSofa {
public:
	virtual ~AbstractSofa() {};

	virtual std::string AssembleSofa() const = 0;

	virtual std::string CreateCollaboration(const AbstractChair& collaborator) const = 0;
};

// derived class for victorian sofas
class VictorianSofa : public AbstractSofa {
public:
	std::string AssembleSofa() const override {
		return "You have created a victorian sofa";
	}

	std::string CreateCollaboration(const AbstractChair& collaborator) const {
		const std::string result = collaborator.AssembleChair();
		return "You have created a victorian sofa and " + result;
	}
};

// derived class for modern sofas
class ModernSofa : public AbstractSofa {
public:
	std::string AssembleSofa() const override {
		return "You have created a modern sofa";
	}

	std::string CreateCollaboration(const AbstractChair& collaborator) const {
		const std::string result = collaborator.AssembleChair();
		return "You have created a modern sofa and " + result;
	}
};

// abstract class for a factory
class AbstractFactory {
public:
	virtual AbstractChair* CreateChair() const = 0;
	virtual AbstractSofa* CreateSofa() const = 0;
};

// derived class for a victorian factory
class VictorianFactory : public AbstractFactory {
public:
	AbstractChair* CreateChair() const override {
		return new VictorianChair();
	}

	AbstractSofa* CreateSofa() const override {
		return new VictorianSofa();
	}
};

// derived class for a modern factory
class ModernFactory : public AbstractFactory {
public:
	AbstractChair* CreateChair() const override {
		return new ModernChair();
	}

	AbstractSofa* CreateSofa() const override {
		return new ModernSofa();
	}
};

// helper function for testing
void ClientCode(const AbstractFactory& factory) {
	const AbstractChair* chair = factory.CreateChair();
	const AbstractSofa* sofa = factory.CreateSofa();

	std::cout << sofa->AssembleSofa() << std::endl;
	std::cout << sofa->CreateCollaboration(*chair) << std::endl;

	delete chair;
	delete sofa;
}

int main() {
	std::cout << "Client: Testing client code with the victorian factory" << std::endl;
	VictorianFactory* victorian_factory = new VictorianFactory();
	ClientCode(*victorian_factory);
	delete victorian_factory;

	std::cout << std::endl;

	std::cout << "Client: Testing client code with the modern factory" << std::endl;
	ModernFactory* modern_factory = new ModernFactory();
	ClientCode(*modern_factory);
	delete modern_factory;

	return 0;
}
