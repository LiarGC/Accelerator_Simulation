#pragma once

#include <iostream>
#include <map>

using namespace std;

typedef void* (*PTRCreateObject)(void);

class ClassFactory {
private:
    map<string, PTRCreateObject> m_classMap;
    ClassFactory() {};

public:
    void* getClassByName(string className);
    void registClass(string name, PTRCreateObject method);
    static ClassFactory& getInstance();
};



class RegisterAction {
public:
    RegisterAction(string className, PTRCreateObject ptrCreateFn);
};

#define REGISTER_h(className)                                           \
    className* objectCreator##className()                               \

#define REGISTER_cpp(className)                                         \
    className* objectCreator##className(){                              \
        return new className;                                           \
    }                                                                   \
    RegisterAction g_creatorRegister##className(                        \
        #className,(PTRCreateObject)objectCreator##className)

// 1.   在.h和.cpp中分别调用这两个宏即可实现类的反射
// 2.   在需要反射的类中加入下列代码以返回类名
//  string GetClassName() const {return typeid(*this).name();}

//使用实例：
// Particle* temp = (Particle*)ClassFactory::getInstance().getClassByName(p_IdealParticle->GetClassName());
// 根据p_IdealParticle的类型创建同样的类（加速器物理中是围绕理想粒子创建出其他相同的粒子）
// 相当于 Particle* temp = new IdealParticle（这一行只是表述意思，实际不能这么写）
// ！！！注意！！！：有new，记得delete