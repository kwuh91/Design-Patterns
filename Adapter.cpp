// an adapter design pattern example, which converts hexadecimal to binary

#include <iostream>	
#include <string>
#include <bitset>

class Target {
public:
	virtual ~Target() = default;

	virtual std::string BinaryRequest() const {
		return "10101010101010010010011011010"; // decimal: 357901530
	}
};

class Adaptee {
public:
	~Adaptee() = default;

	std::string HexRequest() const {
		return "93AD7CC"; // decimal: 154851276
	}
};

class Adapter : public Target {
public:
	Adapter(Adaptee* adaptee) : _adaptee(adaptee) {}

	~Adapter() override { delete _adaptee; }

	std::string BinaryRequest() const override {
		std::string initial_str = _adaptee->HexRequest();

		unsigned int x = std::stoul(initial_str, nullptr, 16);
		std::string result_str = std::bitset<16>(x).to_string();

		return result_str;
	}

private:
	Adaptee* _adaptee;
};

void ClientCode(const Target* target) {
	std::cout << target->BinaryRequest();
}

int main() {
	Target* target = new Target;
	ClientCode(target); // 10101010101010010010011011010

	std::cout << std::endl << std::endl;

	Adaptee* adaptee = new Adaptee;
	std::cout << adaptee->HexRequest(); // 93AD7CC

	std::cout << std::endl << std::endl;

	Adapter* adapter = new Adapter(adaptee);
	ClientCode(adapter); // 1101011111001100

	std::cout << std::endl << std::endl;

	std::cout << adapter->BinaryRequest(); // 1101011111001100
	return 0;
}
