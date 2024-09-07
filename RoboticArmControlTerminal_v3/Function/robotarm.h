#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <QList>
#include <QObject>

// 关节角度信息结构体
class JointAngle : public QObject{
    Q_OBJECT
private:
    float ResetAngle;
    float MaxAngle;
    float MinAngle;
    float DefaultResetAngle;
    float DefaultMaxAngle;
    float DefaultMinAngle;
    float CurAngle;
    float TargetAngle;

public:
    JointAngle();
    JointAngle(float DefaultResetAngle, float DefaultMaxAngle, float DefaultMinAngle);
    ~JointAngle();

    Q_SIGNAL void ResetAngleChange(void);
    Q_SIGNAL void MaxAngleChange(void);
    Q_SIGNAL void MinAngleChange(void);
    Q_SIGNAL void CurAngleChange(void);
    Q_SIGNAL void TargetAngleChange(void);

    // ResetAngle
    bool setResetAngle(float angle);
    float getResetAngle() const;

    // MaxAngle
    bool setMaxAngle(float angle);
    float getMaxAngle() const;

    // MinAngle
    bool setMinAngle(float angle);
    float getMinAngle() const;

    // CurAngle
    bool setCurAngle(float angle);
    float getCurAngle() const;

    // TargetAngle
    bool setTargetAngle(float angle);
    float getTargetAngle() const;

    // DefaultResetAngle
    bool setDefaultResetAngle(float angle);
    float getDefaultResetAngle() const;

    // DefaultMaxAngle
    bool setDefaultMaxAngle(float angle);
    float getDefaultMaxAngle() const;

    // DefaultMinAngle
    bool setDefaultMinAngle(float angle);
    float getDefaultMinAngle() const;
};


class RobotArm
{
public:
    RobotArm();
    ~RobotArm();

    void addJoint(JointAngle *joint);

    // 当前角度
    float getCurAngle(int jointIndex) const;
    bool setCurAngle(int jointIndex, float angle);

    // 目标角度
    bool setTargetAngle(int jointIndex, float angle);
    float getTargetAngle(int jointIndex) const;

    // 最大角度
    bool setMaxAngle(int jointIndex, float angle);
    float getMaxAngle(int jointIndex) const;

    // MinAngle
    bool setMinAngle(int jointIndex, float angle);
    float getMinAngle(int jointIndex) const;

    // ResetAngle
    bool setResetAngle(int jointIndex, float angle);
    float getResetAngle(int jointIndex) const;

    // 复位机械臂
    void resetAllJointsAngle(void);

    // 复位机械臂参数
    void resetAllJointsParam(void);

    // 获取所有舵机目标角度
    QVector<int> getAllTargetAngle(void);

    // 获取所有舵机的当前角度
    QVector<int> getAllCurAngle(void);

private:
    QList<JointAngle*> joints;

};

#endif // ROBOTARM_H
