#include "cpp_Reflex.h"

void* ClassFactory::getClassByName(string className) {
    map<string, PTRCreateObject>::const_iterator iter;
    if (className.substr(0, 6) == "class ") className.erase(0, 6);
    iter = m_classMap.find(className);
    if (iter == m_classMap.end())
        return NULL;
    else
        return iter->second();//���ص���PTRCreateObject���͵ĺ���ָ�룬����ת��Ϊvoid*
}

void ClassFactory::registClass(string name, PTRCreateObject method) {
    m_classMap.insert(pair<string, PTRCreateObject>(name, method));
}

ClassFactory& ClassFactory::getInstance() {
    static ClassFactory sLo_factory;
    return sLo_factory;
}

RegisterAction::RegisterAction(string className, PTRCreateObject ptrCreateFn)
{
    ClassFactory::getInstance().registClass(className, ptrCreateFn);
}

