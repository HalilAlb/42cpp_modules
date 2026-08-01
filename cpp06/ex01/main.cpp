#include "Serializer.hpp"
#include "Data.hpp"

#include <iostream>

int main()
{
	Data original;
	original.id = 42;
	original.name = "Marvin";

	Data* originalPtr = &original;

	std::cout << "Original pointer: " << originalPtr
			  << "  id=" << originalPtr->id
			  << "  name=" << originalPtr->name << std::endl;


	std::cout << "\n=== Test 1: serialize → uintptr_t ===" << std::endl;
	uintptr_t raw = Serializer::serialize(originalPtr);
	std::cout << "Serialized (uintptr_t): " << raw
			  << "  (hex: 0x" << std::hex << raw << std::dec << ")" << std::endl;


	std::cout << "\n=== Test 2: deserialize → Data* (eşitlik kontrolü) ===" << std::endl;
	Data* roundtrip = Serializer::deserialize(raw);
	std::cout << "Deserialized pointer: " << roundtrip << std::endl;

	if (roundtrip == originalPtr)
		std::cout << "OK: round-trip pointer'lar EŞİT." << std::endl;
	else
		std::cout << "FAIL: pointer'lar farklı!" << std::endl;


	std::cout << "\n=== Test 3: round-trip sonrası veri erişimi ===" << std::endl;
	std::cout << "  id=" << roundtrip->id << "  name=" << roundtrip->name << std::endl;


	std::cout << "\n=== Test 4: NULL pointer round-trip ===" << std::endl;
	uintptr_t rawNull = Serializer::serialize(NULL);
	Data*     backNull = Serializer::deserialize(rawNull);
	std::cout << "NULL → " << rawNull << " → " << backNull << std::endl;

	return 0;
}
