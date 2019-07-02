#ifndef _ROS_aeropendulum_common_messages_GraphPlotData_h
#define _ROS_aeropendulum_common_messages_GraphPlotData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace aeropendulum_common_messages
{

  class GraphPlotData : public ros::Msg
  {
    public:
      float angle;
      uint32_t nSample;
      float setPointAngle;
      float angleError;
      uint8_t controlSignal;

    GraphPlotData():
      angle(0),
      nSample(0),
      setPointAngle(0),
      angleError(0),
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
      *(outbuffer + offset + 0) = (this->nSample >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->nSample >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->nSample >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->nSample >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nSample);
      union {
        float real;
        uint32_t base;
      } u_setPointAngle;
      u_setPointAngle.real = this->setPointAngle;
      *(outbuffer + offset + 0) = (u_setPointAngle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_setPointAngle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_setPointAngle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_setPointAngle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->setPointAngle);
      union {
        float real;
        uint32_t base;
      } u_angleError;
      u_angleError.real = this->angleError;
      *(outbuffer + offset + 0) = (u_angleError.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angleError.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angleError.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angleError.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angleError);
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
      this->nSample =  ((uint32_t) (*(inbuffer + offset)));
      this->nSample |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->nSample |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->nSample |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->nSample);
      union {
        float real;
        uint32_t base;
      } u_setPointAngle;
      u_setPointAngle.base = 0;
      u_setPointAngle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_setPointAngle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_setPointAngle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_setPointAngle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->setPointAngle = u_setPointAngle.real;
      offset += sizeof(this->setPointAngle);
      union {
        float real;
        uint32_t base;
      } u_angleError;
      u_angleError.base = 0;
      u_angleError.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angleError.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angleError.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angleError.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angleError = u_angleError.real;
      offset += sizeof(this->angleError);
      this->controlSignal =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->controlSignal);
     return offset;
    }

    const char * getType(){ return "aeropendulum_common_messages/GraphPlotData"; };
    const char * getMD5(){ return "e4762c53c8225f46070739c0ad3233bd"; };

  };

}
#endif