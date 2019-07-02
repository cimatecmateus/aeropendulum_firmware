#ifndef _ROS_SERVICE_GetSteadyState_h
#define _ROS_SERVICE_GetSteadyState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aeropendulum_common_messages
{

static const char GETSTEADYSTATE[] = "aeropendulum_common_messages/GetSteadyState";

  class GetSteadyStateRequest : public ros::Msg
  {
    public:

    GetSteadyStateRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETSTEADYSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetSteadyStateResponse : public ros::Msg
  {
    public:
      float angle;
      uint8_t controlSignal;

    GetSteadyStateResponse():
      angle(0),
      controlSignal(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle);
      *(outbuffer + offset + 0) = (this->controlSignal >> (8 * 0)) & 0xFF;
      offset += sizeof(this->controlSignal);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      this->controlSignal =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->controlSignal);
     return offset;
    }

    const char * getType(){ return GETSTEADYSTATE; };
    const char * getMD5(){ return "8e953021db4399b51229ee458af92582"; };

  };

  class GetSteadyState {
    public:
    typedef GetSteadyStateRequest Request;
    typedef GetSteadyStateResponse Response;
  };

}
#endif
