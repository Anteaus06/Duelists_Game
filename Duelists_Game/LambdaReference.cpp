/*#include <iostream>
#include <functional>

int DoSomethingWithCallback(std::function<void()> callback)
{
	// do stuff
	int x = 10;
	int y = 20;

	callback();
	return x * y + 15;
}

void PrintToConsole()
{
	std::cout << "Lambda Callback" << std::endl;
}

int main()
{

	DoSomethingWithCallback(PrintToConsole);
	// or do this
	DoSomethingWithCallback([]() {std::cout << "Lambda Callback" << std::endl; });
	
	return 0;
	//int y = 5;

	//int x = 10;

	//auto myAutoLambda = [=]() // the = means this x and y equal the top
	//	{
	//	std::cout << "x: " << x << "y: " << y << std::endl;
	//	};
	//auto myAutoLambda = [&]() // the & is referencing the original so it can be modified 
	//	{
	//		x = x * y;
	//		std::cout << "x: " << x << std::endl;
	//	};

	//int x=5,
	//int y = 10;

	//auto lambda = [x, &y]() 
	//	{
	//		//x is captured by value copy, y is captured by reference
	//		std::cout "  x" << x << " y" << y std::endl
	//			// changing y will affect what the lambda sees but changing x won't
	//			x = 30;
	//		y = 14;
	//		lambda(); // output: x: 5, y: 14

	//	}
	
}

//[] no variables are captured.
//[=] captures variables from surrounding scope by value
//[&] captures variables from surrounding scope by reference
//[x] captures only the x by value
//[&x] captures only the variable x by reference
*/