#include "robotarm.h"
#include <QDebug>

RobotArm::RobotArm()
{

}

void RobotArm::addJoint(JointAngle *joint)
{
    joints.append(joint);
}

float RobotArm::getCurAngle(int jointIndex) const
{
    if(jointIndex < joints.size())
    {
        return joints[jointIndex]->getCurAngle();
    }
    else
    {
        return -1;
    }
}

bool RobotArm::setCurAngle(int jointIndex, float angle)
{
    if(jointIndex < joints.size())
    {
        if(joints[jointIndex]->setCurAngle(angle))
        {
            qDebug() << "CurAngle[" << jointIndex << "] 设置成功: " << angle;
            return true;
        }
        else
        {
            qDebug() << "CurAngle[" << jointIndex << "] 设置失败: " << angle;
            return false;
        }
    }
    qDebug() << "CurAngle[" << jointIndex << "] 不存在";
    return false;
}

bool RobotArm::setTargetAngle(int jointIndex, float angle) {
    if(jointIndex < joints.size()) {
        if(joints[jointIndex]->setTargetAngle(angle)) {
            qDebug() << "TargetAngle[" << jointIndex << "] 设置成功: " << angle;
            return true;
        } else {
            qDebug() << "TargetAngle[" << jointIndex << "] 设置失败: " << angle;
            return false;
        }
    }
    qDebug() << "TargetAngle[" << jointIndex << "] 不存在";
    return false;
}

float RobotArm::getTargetAngle(int jointIndex) const {
    if(jointIndex < joints.size()) {
        return joints[jointIndex]->getTargetAngle();
    } else {
        return -1;
    }
}

bool RobotArm::setMaxAngle(int jointIndex, float angle) {
    if(jointIndex < joints.size()) {
        if(joints[jointIndex]->setMaxAngle(angle)) {
            qDebug() << "MaxAngle[" << jointIndex << "] 设置成功: " << angle;
            return true;
        } else {
            qDebug() << "MaxAngle[" << jointIndex << "] 设置失败: " << angle;
            return false;
        }
    }
    qDebug() << "MaxAngle[" << jointIndex << "] 不存在";
    return false;
}

float RobotArm::getMaxAngle(int jointIndex) const {
    if(jointIndex < joints.size()) {
        return joints[jointIndex]->getMaxAngle();
    } else {
        return -1;
    }
}

bool RobotArm::setMinAngle(int jointIndex, float angle) {
    if(jointIndex < joints.size()) {
        if(joints[jointIndex]->setMinAngle(angle)) {
            qDebug() << "MinAngle[" << jointIndex << "] 设置成功: " << angle;
            return true;
        } else {
            qDebug() << "MinAngle[" << jointIndex << "] 设置失败: " << angle;
            return false;
        }
    }
    qDebug() << "MinAngle[" << jointIndex << "] 不存在";
    return false;
}

float RobotArm::getMinAngle(int jointIndex) const {
    if(jointIndex < joints.size()) {
        return joints[jointIndex]->getMinAngle();
    } else {
        return -1;
    }
}

bool RobotArm::setResetAngle(int jointIndex, float angle) {
    if(jointIndex < joints.size()) {
        if(joints[jointIndex]->setResetAngle(angle)) {
            qDebug() << "ResetAngle[" << jointIndex << "] 设置成功: " << angle;
            return true;
        } else {
            qDebug() << "ResetAngle[" << jointIndex << "] 设置失败: " << angle;
            return false;
        }
    }
    qDebug() << "ResetAngle[" << jointIndex << "] 不存在";
    return false;
}

float RobotArm::getResetAngle(int jointIndex) const {
    if(jointIndex < joints.size()) {
        return joints[jointIndex]->getResetAngle();
    } else {
        return -1; // 或者抛出异常
    }
}

void RobotArm::resetAllJointsAngle()
{
    for (int i = 0; i < joints.size(); ++i)
    {
        joints[i]->setTargetAngle(joints[i]->getResetAngle());
    }
}

void RobotArm::resetAllJointsParam()
{
    for (int i = 0; i < joints.size(); ++i) {
        joints[i]->setMaxAngle(joints[i]->getDefaultMaxAngle());
        joints[i]->setMinAngle(joints[i]->getDefaultMinAngle());
        joints[i]->setResetAngle(joints[i]->getDefaultResetAngle());
    }
}

QVector<int> RobotArm::getAllTargetAngle()
{
    QVector<int> angelSet;
    for (int i = 0; i < joints.size(); ++i) {
        angelSet.append(joints[i]->getTargetAngle());
    }
    return angelSet;
}

QVector<int> RobotArm::getAllCurAngle()
{
    QVector<int> angelSet;
    for (int i = 0; i < joints.size(); ++i) {
        angelSet.append(joints[i]->getCurAngle());
    }
    return angelSet;
}


JointAngle::JointAngle()
{
    DefaultResetAngle = 90.0;
    DefaultMaxAngle =180.0;
    DefaultMinAngle = 0.0;
    MaxAngle = DefaultMaxAngle;
    MinAngle = DefaultMinAngle;
    ResetAngle = DefaultResetAngle;
    CurAngle = ResetAngle;
    TargetAngle = ResetAngle;
}

JointAngle::JointAngle(float DefaultResetAngle, float DefaultMaxAngle, float DefaultMinAngle)
{
    this->DefaultResetAngle = DefaultResetAngle;
    this->DefaultMaxAngle =DefaultMaxAngle;
    this->DefaultMinAngle = DefaultMinAngle;
    MaxAngle = this->DefaultMaxAngle;
    MinAngle = this->DefaultMinAngle;
    ResetAngle = this->DefaultResetAngle;
    CurAngle = ResetAngle;
    TargetAngle = ResetAngle;
}

JointAngle::~JointAngle()
{

}

bool JointAngle::setResetAngle(float angle)
{
    if(ResetAngle == angle)
    {
        return true;
    }
    if(angle > MaxAngle || angle < MinAngle)
    {
        return false;
    }
    else
    {
        ResetAngle = angle;
        ResetAngleChange();
        return true;
    }
}

float JointAngle::getResetAngle() const
{
    return ResetAngle;
}

bool JointAngle::setMaxAngle(float angle)
{
    if(MaxAngle == angle)
    {
        return true;
    }
    if(angle < 0 || angle > 360)
    {
        return false;
    }
    else
    {
        MaxAngle = angle;
        MaxAngleChange();
        return true;
    }
}

float JointAngle::getMaxAngle() const
{
    return MaxAngle;
}

bool JointAngle::setMinAngle(float angle)
{
    if(MinAngle == angle)
    {
        return true;
    }
    if(angle < 0 || angle > 360)
    {
        return false;
    }
    else
    {
        MinAngle = angle;
        MinAngleChange();
        return true;
    }
}

float JointAngle::getMinAngle() const
{
    return MinAngle;
}

bool JointAngle::setCurAngle(float angle)
{
    if(CurAngle == angle)
    {
        return true;
    }
    if(angle > MaxAngle || angle < MinAngle)
    {
        return false;
    }
    else
    {
        CurAngle = angle;
        CurAngleChange();
        return true;
    }
}

float JointAngle::getCurAngle() const
{
    return CurAngle;
}

bool JointAngle::setTargetAngle(float angle)
{
    if(TargetAngle == angle)
    {
        return true;
    }
    if(angle > MaxAngle || angle < MinAngle)
    {
        return false;
    }
    else
    {
        TargetAngle = angle;
        TargetAngleChange();
        qDebug() << "Target Angle Changed [" << TargetAngle << "]";
        return true;
    }
}

float JointAngle::getTargetAngle() const
{
    return TargetAngle;
}

bool JointAngle::setDefaultResetAngle(float angle)
{
    if(angle > DefaultMaxAngle || angle < DefaultMinAngle)
    {
        return false;
    }
    else
    {
        TargetAngle = angle;
        return true;
    }
}

float JointAngle::getDefaultResetAngle() const
{
    return DefaultResetAngle;
}

bool JointAngle::setDefaultMaxAngle(float angle)
{
    if(angle < 0 || angle > 360)
    {
        return false;
    }
    else
    {
        DefaultMaxAngle = angle;
        return true;
    }
}

float JointAngle::getDefaultMaxAngle() const
{
    return DefaultMaxAngle;
}

bool JointAngle::setDefaultMinAngle(float angle)
{
    if(angle < 0 || angle > 360)
    {
        return false;
    }
    else
    {
        DefaultMinAngle = angle;
        return true;
    }
}

float JointAngle::getDefaultMinAngle() const
{
    return DefaultMinAngle;
}






