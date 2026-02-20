#pragma once 


class ITickable{
public:
  virtual void tick() = 0;


  virtual ~ITickable(){}
};

