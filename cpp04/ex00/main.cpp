#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void printHeader(const std::string& title)
{
	std::cout << "\n========================================" << std::endl;
	std::cout << title << std::endl;
	std::cout << "========================================" << std::endl;
}

void testSubjectExample()
{
	printHeader("SUBJECT EXAMPLE TEST");
	
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\n--- Type Tests ---" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	
	std::cout << "\n--- Sound Tests ---" << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();
	
	std::cout << "\n--- Cleanup ---" << std::endl;
	delete i;
	delete j;
	delete meta;
}

void testPolymorphism()
{
	printHeader("POLYMORPHISM TEST");
	
	std::cout << "\n--- Creating animals ---" << std::endl;
	Animal* animals[3];
	animals[0] = new Animal();
	animals[1] = new Dog();
	animals[2] = new Cat();
	
	std::cout << "\n--- Testing polymorphic behavior ---" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Animal type: " << animals[i]->getType() << " says: ";
		animals[i]->makeSound();
	}
	
	std::cout << "\n--- Cleanup ---" << std::endl;
	for (int i = 0; i < 3; i++)
		delete animals[i];
}

void testCopyConstructor()
{
	printHeader("COPY CONSTRUCTOR TEST");
	
	std::cout << "\n--- Creating original dog ---" << std::endl;
	Dog originalDog;
	
	std::cout << "\n--- Creating copy of dog ---" << std::endl;
	Dog copyDog(originalDog);
	
	std::cout << "\n--- Testing both dogs ---" << std::endl;
	std::cout << "Original: " << originalDog.getType() << " - ";
	originalDog.makeSound();
	std::cout << "Copy: " << copyDog.getType() << " - ";
	copyDog.makeSound();
	
	std::cout << "\n--- Cleanup (automatic) ---" << std::endl;
}

void testAssignmentOperator()
{
	printHeader("ASSIGNMENT OPERATOR TEST");
	
	std::cout << "\n--- Creating cat and dog ---" << std::endl;
	Cat cat1;
	Cat cat2;
	
	std::cout << "\n--- Before assignment ---" << std::endl;
	std::cout << "Cat1: " << cat1.getType() << " - ";
	cat1.makeSound();
	std::cout << "Cat2: " << cat2.getType() << " - ";
	cat2.makeSound();
	
	std::cout << "\n--- Assignment operation ---" << std::endl;
	cat2 = cat1;
	
	std::cout << "\n--- After assignment ---" << std::endl;
	std::cout << "Cat1: " << cat1.getType() << " - ";
	cat1.makeSound();
	std::cout << "Cat2: " << cat2.getType() << " - ";
	cat2.makeSound();
	
	std::cout << "\n--- Cleanup (automatic) ---" << std::endl;
}

void testWrongAnimal()
{
	printHeader("WRONG ANIMAL TEST (No Polymorphism)");
	
	std::cout << "\n--- Creating wrong animals ---" << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();
	
	std::cout << "\n--- Type Tests ---" << std::endl;
	std::cout << "WrongAnimal type: " << wrongMeta->getType() << std::endl;
	std::cout << "WrongCat type: " << wrongCat->getType() << std::endl;
	
	std::cout << "\n--- Sound Tests (Notice: Both use WrongAnimal sound!) ---" << std::endl;
	std::cout << "WrongAnimal sound: ";
	wrongMeta->makeSound();
	std::cout << "WrongCat sound (but outputs WrongAnimal sound): ";
	wrongCat->makeSound(); // Will output WrongAnimal sound because makeSound() is not virtual!
	
	std::cout << "\n--- Cleanup ---" << std::endl;
	delete wrongCat;
	delete wrongMeta;
}

void testStackVsHeap()
{
	printHeader("STACK VS HEAP ALLOCATION TEST");
	
	std::cout << "\n--- Stack allocation ---" << std::endl;
	Dog stackDog;
	Cat stackCat;
	
	std::cout << "\n--- Testing stack animals ---" << std::endl;
	std::cout << stackDog.getType() << " says: ";
	stackDog.makeSound();
	std::cout << stackCat.getType() << " says: ";
	stackCat.makeSound();
	
	std::cout << "\n--- Heap allocation ---" << std::endl;
	Dog* heapDog = new Dog();
	Cat* heapCat = new Cat();
	
	std::cout << "\n--- Testing heap animals ---" << std::endl;
	std::cout << heapDog->getType() << " says: ";
	heapDog->makeSound();
	std::cout << heapCat->getType() << " says: ";
	heapCat->makeSound();
	
	std::cout << "\n--- Cleanup heap ---" << std::endl;
	delete heapDog;
	delete heapCat;
	
	std::cout << "\n--- Cleanup stack (automatic) ---" << std::endl;
}

void testArrayOfAnimals()
{
	printHeader("ARRAY OF ANIMALS TEST");
	
	std::cout << "\n--- Creating array of animals ---" << std::endl;
	const int SIZE = 6;
	Animal* zoo[SIZE];
	
	for (int i = 0; i < SIZE / 2; i++)
		zoo[i] = new Dog();
	for (int i = SIZE / 2; i < SIZE; i++)
		zoo[i] = new Cat();
	
	std::cout << "\n--- Animals in the zoo ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
	{
		std::cout << "Animal " << i << " - Type: " << zoo[i]->getType() << " - Sound: ";
		zoo[i]->makeSound();
	}
	
	std::cout << "\n--- Cleanup ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
		delete zoo[i];
}

int main()
{
	testSubjectExample();
	testPolymorphism();
	testCopyConstructor();
	testAssignmentOperator();
	testWrongAnimal();
	testStackVsHeap();
	testArrayOfAnimals();
	
	printHeader("ALL TESTS COMPLETED");
	
	return 0;
}
