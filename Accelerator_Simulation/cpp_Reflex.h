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

// 1.   ��.h��.cpp�зֱ�����������꼴��ʵ����ķ���
// 2.   ����Ҫ��������м������д����Է�������
//  string GetClassName() const {return typeid(*this).name();}

//ʹ��ʵ����
// Particle* temp = (Particle*)ClassFactory::getInstance().getClassByName(p_IdealParticle->GetClassName());
// ����p_IdealParticle�����ʹ���ͬ�����ࣨ��������������Χ���������Ӵ�����������ͬ�����ӣ�
// �൱�� Particle* temp = new IdealParticle����һ��ֻ�Ǳ�����˼��ʵ�ʲ�����ôд��
// ������ע�⣡��������new���ǵ�delete