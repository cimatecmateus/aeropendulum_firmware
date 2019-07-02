#ifndef _ROS_SERVICE_GetPid_h
#define _ROS_SERVICE_GetPid_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aeropendulum_common_messages
{

static const char GETPID[] = "aeropendulum_common_messages/GetPid";

  class GetPidRequest : public ros::Msg
  {
    public:

    GetPidRequest()
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

    const char * getType(){ return GETPID; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetPidResponse : public ros::Msg
  {
    public:
      float kp;
      float ki;
      float kd;
      float pidPeriod;

    GetPidResponse():
      kp(0),
      ki(0),
      kd(0),
      pidPeriod(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_kp;
      u_kp.real = this->kp;
      *(outbuffer + offset + 0) = (u_kp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kp.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kp);
      union {
        float real;
        uint32_t base;
      } u_ki;
      u_ki.real = this->ki;
      *(outbuffer + offset + 0) = (u_ki.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ki.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ki.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ki.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ki);
      union {
        float real;
        uint32_t base;
      } u_kd;
      u_kd.real = this->kd;
      *(outbuffer + offset + 0) = (u_kd.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_kd.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_kd.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_kd.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->kd);
      union {
        float real;
        uint32_t base;
      } u_pidPeriod;
      u_pidPeriod.real = this->pidPeriod;
      *(outbuffer + offset + 0) = (u_pidPeriod.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pidPeriod.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pidPeriod.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pidPeriod.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pidPeriod);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_kp;
      u_kp.base = 0;
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kp.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kp = u_kp.real;
      offset += sizeof(this->kp);
      union {
        float real;
        uint32_t base;
      } u_ki;
      u_ki.base = 0;
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ki.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ki = u_ki.real;
      offset += sizeof(this->ki);
      union {
        float real;
        uint32_t base;
      } u_kd;
      u_kd.base = 0;
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_kd.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->kd = u_kd.real;
      offset += sizeof(this->kd);
      union {
        float real;
        uint32_t base;
      } u_pidPeriod;
      u_pidPeriod.base = 0;
      u_pidPeriod.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pidPeriod.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pidPeriod.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pidPeriod.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pidPeriod = u_pidPeriod.real;
      offset += sizeof(this->pidPeriod);
     return offset;
    }

    const char * getType(){ return GETPID; };
    const char * getMD5(){ return "ca14d2914fbd2382c632d5cc189a8548"; };

  };

  class GetPid {
    public:
    typedef GetPidRequest Request;
    typedef GetPidResponse Response;
  };

}
#endif
