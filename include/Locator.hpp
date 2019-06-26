
// As seen in Game Programming Patterns - Decoupling Patterns:
//	  https://gameprogrammingpatterns.com/service-locator.html

template <typename T>
class Locator
{
public:
	static T* getService() const 
	{ return _service; }

	static void provide(T* service)
	{ _service = service; }

private:
	static T* _service;
};