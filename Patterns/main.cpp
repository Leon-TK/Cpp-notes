#include "Command.hpp"
#include "Template method.hpp"
#include "Strategy.hpp"
#include "Adapter.hpp"
#include "Decorator.hpp"
#include "Bridge.hpp"
#include "Facade.hpp"
//#include "Mediator.h"
#include "Visitor.hpp"
#include "Observer.hpp"
//#include "State.hpp"
#include "Chain.hpp"
#include "Memento.hpp"
#include "Proxy.hpp"
//#include "Lightweight.hpp"
#include "Builder.hpp"

//TODO: pointers' memory allocation
//TODO: format the code by rules/convention
int main() {
    CommandPattern::Run();
    TemplateMethodPattern::Run();
    StrategyPattern::Run();
    AdapterPattern::Run();
    DecoratorPattern::Run();
    BridgePattern::Run();
    FacadePattern::Run();
    //MediatorPattern::Run();
    VisitorPattern::Run();
    ObserverPattern::Run();
    ChainPattern::Run();
    MementoPattern::Run();
    ProxyPattern::Run();
    //LightweightPattern::Run();
    BuilderPattern::Run();
    return 0;
}