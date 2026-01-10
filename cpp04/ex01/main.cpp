#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

void testBasicRequirements()
{
	std::cout << "\n========== BASIC REQUIREMENTS TEST ==========" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	delete j;
	delete i;
}

void testAnimalArray()
{
	std::cout << "\n========== ANIMAL ARRAY TEST ==========" << std::endl;
	const int arraySize = 6;
	Animal* animals[arraySize];
	
	std::cout << "\n--- Creating half Dogs and half Cats ---" << std::endl;
	for (int idx = 0; idx < arraySize / 2; idx++)
	{
		std::cout << "\nCreating Dog " << idx << ":" << std::endl;
		animals[idx] = new Dog();
	}
	
	for (int idx = arraySize / 2; idx < arraySize; idx++)
	{
		std::cout << "\nCreating Cat " << idx << ":" << std::endl;
		animals[idx] = new Cat();
	}
	
	std::cout << "\n--- Testing makeSound() for all animals ---" << std::endl;
	for (int idx = 0; idx < arraySize; idx++)
	{
		std::cout << animals[idx]->getType() << " says: ";
		animals[idx]->makeSound();
	}
	
	std::cout << "\n--- Deleting all animals ---" << std::endl;
	for (int idx = 0; idx < arraySize; idx++)
	{
		std::cout << "\nDeleting animal " << idx << " (" << animals[idx]->getType() << "):" << std::endl;
		delete animals[idx];
	}
}

void testDeepCopy()
{
	std::cout << "\n========== DEEP COPY TEST ==========" << std::endl;
	
	std::cout << "\n--- Testing Dog deep copy ---" << std::endl;
	Dog* originalDog = new Dog();
	originalDog->getBrain()->setIdea(0, "I love bones!");
	originalDog->getBrain()->setIdea(1, "Chase the cat!");
	originalDog->getBrain()->setIdea(2, "Play fetch!");
	
	std::cout << "\n--- Creating copy of Dog ---" << std::endl;
	Dog* copiedDog = new Dog(*originalDog);
	
	std::cout << "\nOriginal Dog's ideas:" << std::endl;
	std::cout << "  Idea 0: " << originalDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "  Idea 1: " << originalDog->getBrain()->getIdea(1) << std::endl;
	std::cout << "  Idea 2: " << originalDog->getBrain()->getIdea(2) << std::endl;
	
	std::cout << "\nCopied Dog's ideas:" << std::endl;
	std::cout << "  Idea 0: " << copiedDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "  Idea 1: " << copiedDog->getBrain()->getIdea(1) << std::endl;
	std::cout << "  Idea 2: " << copiedDog->getBrain()->getIdea(2) << std::endl;
	
	std::cout << "\n--- Modifying original Dog's ideas ---" << std::endl;
	originalDog->getBrain()->setIdea(0, "Modified idea!");
	
	std::cout << "\nOriginal Dog's idea 0 (modified): " << originalDog->getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied Dog's idea 0 (should be unchanged): " << copiedDog->getBrain()->getIdea(0) << std::endl;
	
	std::cout << "\n--- Checking Brain addresses (should be different) ---" << std::endl;
	std::cout << "Original Dog Brain address: " << originalDog->getBrain() << std::endl;
	std::cout << "Copied Dog Brain address:   " << copiedDog->getBrain() << std::endl;
	
	if (originalDog->getBrain() != copiedDog->getBrain())
		std::cout << "✓ Deep copy successful: Brain objects are different!" << std::endl;
	else
		std::cout << "✗ Shallow copy detected: Brain objects are the same!" << std::endl;
	
	std::cout << "\n--- Deleting Dogs ---" << std::endl;
	delete originalDog;
	delete copiedDog;
	
	std::cout << "\n--- Testing Cat deep copy ---" << std::endl;
	Cat* originalCat = new Cat();
	originalCat->getBrain()->setIdea(0, "Sleep all day");
	originalCat->getBrain()->setIdea(1, "Hunt mice");
	
	Cat* copiedCat = new Cat(*originalCat);
	
	std::cout << "\n--- Checking Cat Brain addresses (should be different) ---" << std::endl;
	std::cout << "Original Cat Brain address: " << originalCat->getBrain() << std::endl;
	std::cout << "Copied Cat Brain address:   " << copiedCat->getBrain() << std::endl;
	
	if (originalCat->getBrain() != copiedCat->getBrain())
		std::cout << "✓ Deep copy successful: Brain objects are different!" << std::endl;
	else
		std::cout << "✗ Shallow copy detected: Brain objects are the same!" << std::endl;
	
	std::cout << "\n--- Deleting Cats ---" << std::endl;
	delete originalCat;
	delete copiedCat;
}

void testAssignmentOperator()
{
	std::cout << "\n========== ASSIGNMENT OPERATOR TEST ==========" << std::endl;
	
	Dog dog1;
	dog1.getBrain()->setIdea(0, "First dog's idea");
	
	Dog dog2;
	dog2.getBrain()->setIdea(0, "Second dog's idea");
	
	std::cout << "\nBefore assignment:" << std::endl;
	std::cout << "Dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
	std::cout << "Dog2 idea: " << dog2.getBrain()->getIdea(0) << std::endl;
	
	std::cout << "\n--- Assigning dog1 to dog2 ---" << std::endl;
	dog2 = dog1;
	
	std::cout << "\nAfter assignment:" << std::endl;
	std::cout << "Dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
	std::cout << "Dog2 idea: " << dog2.getBrain()->getIdea(0) << std::endl;
	
	std::cout << "\n--- Modifying dog1's idea ---" << std::endl;
	dog1.getBrain()->setIdea(0, "Modified first dog's idea");
	
	std::cout << "\nAfter modification:" << std::endl;
	std::cout << "Dog1 idea: " << dog1.getBrain()->getIdea(0) << std::endl;
	std::cout << "Dog2 idea (should be unchanged): " << dog2.getBrain()->getIdea(0) << std::endl;
	
	if (dog1.getBrain() != dog2.getBrain())
		std::cout << "✓ Deep copy successful: Brain objects are different!" << std::endl;
	else
		std::cout << "✗ Shallow copy detected: Brain objects are the same!" << std::endl;
}

int main()
{
	testBasicRequirements();
	testAnimalArray();
	testDeepCopy();
	testAssignmentOperator();
	
	std::cout << "\n========== ALL TESTS COMPLETED ==========" << std::endl;
	std::cout << "\nRun with valgrind to check for memory leaks:" << std::endl;
	std::cout << "valgrind --leak-check=full ./brain" << std::endl;
	
	return 0;
}
