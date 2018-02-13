#include "memorytests.h"
#include "types/nonpersistentstring.h"
#include "memory/memorymanager.h"
#include "log/logger.h"
#include <iostream>
namespace kurobako::tests
{
	bool RunNonPersistentStringTests()
	{
		// Unit test for NonPersistentStringTest.
		{
			// Test 1.
			kurobako::NonPersistentString testStr = kurobako::NonPersistentString("This string should be gone");

			uint64 totalBytes = memory::memory_manager::STRING_BUFFER_SIZE;
			for (int i = 0; i < totalBytes - testStr.GetLength() - 1; ++i)
			{
				kurobako::NonPersistentString str = kurobako::NonPersistentString("", i);
			}

			const char* str = "If this string shows in full, it works!";
			kurobako::NonPersistentString CurrentString = kurobako::NonPersistentString(str);

			if (strcmp(testStr.Get(), str) != 0 && 
				CurrentString.Get() == testStr.Get())
			{
				LOG_INFO(kurobako::NonPersistentString("NonPersistentString::Circluar allocation failed."), 5);
				return false;
			}
			else
			{
				LOG_INFO(kurobako::NonPersistentString("NonPersistentString::Circluar allocation Success!."), 5);
			}
		}

		memory::memory_manager::GetMemoryManager().GetStringBuffer().reset();

		// Test 2.
		{
			kurobako::NonPersistentString testStr = kurobako::NonPersistentString("This string should be be here");

			uint64 totalBytes = memory::memory_manager::STRING_BUFFER_SIZE;
			for (int i = 0; i < totalBytes - testStr.GetLength()*2 -2; ++i)
			{
				kurobako::NonPersistentString str = kurobako::NonPersistentString("", i);
			}

			const char* str = "Should not wipe out other str";
			kurobako::NonPersistentString CurrentString = kurobako::NonPersistentString(str);

			if (strcmp(testStr.Get(), str) == 0 || 
				CurrentString.Get() == testStr.Get())
			{
				LOG_INFO(kurobako::NonPersistentString("NonPersistentString::Failed size tests."), 5);
				return false;
			}
			else
			{
				LOG_INFO(kurobako::NonPersistentString("NonPersistentString::Passed size tests!."), 5);
			}
		}

		// Test 3.
		{
			kurobako::NonPersistentString testStr = kurobako::NonPersistentString("This string should be wiped!!");

			uint64 totalBytes = memory::memory_manager::STRING_BUFFER_SIZE;
			for (int i = 0; i < totalBytes - testStr.GetLength() * 2 - 1 ; ++i)
			{
				kurobako::NonPersistentString str = kurobako::NonPersistentString(" ", i);
			}

			const char* str = "Should wipe out the other str";
			kurobako::NonPersistentString CurrentString = kurobako::NonPersistentString(str);

			if (strcmp(testStr.Get(), str) == 0 ||
				CurrentString.Get() == testStr.Get())
			{
				LOG_INFO(kurobako::NonPersistentString("NonPersistentString::Failed size tests."), 5);
				return false;
			}
			else
			{
				LOG_INFO(kurobako::NonPersistentString("NonPersistentString::Passed size tests!."), 5);
			}
		}

        // Test 4.
        {
            int* arr[10];
            for (int i = 0; i < 10; ++i)
            {
                arr[i] = kurobako::memory::HeapNew<int>("TestInt");
                *arr[i] = i;
            }
            for (int i = 0; i < 10; ++i)
            {
                std::cout << *arr[i] << " ";
            }
        }

		return true;
	}

    
    bool RunMemoryTests()
    {
		RunNonPersistentStringTests();


		return true;
    }
}