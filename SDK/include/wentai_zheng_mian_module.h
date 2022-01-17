/*
 * @Descripttion:
 * @version:
 * @Author: max.ma
 * @Date: 2020-11-06 11:49:09
 * @LastEditors: max.ma
 * @LastEditTime: 2020-11-12 17:04:02
 */

#ifndef __WENTAI_ZHENG_MIAN_MODULE_H__
#define __WENTAI_ZHENG_MIAN_MODULE_H__

#include "ISegmentationModule.h"

namespace smartmore {
struct WenTaiZhengMianResponse : SegmentationResponse {
    std::map<int, size_t> nums;
};

class DLL_API WenTaiZhengMianModule : public ISegmentationModule {
   public:
    WenTaiZhengMianModule();
    ~WenTaiZhengMianModule();

    /**
            sdk版本号
            @return sdk版本号字符串
        */
    std::string Version() override;
    /**
            sdk初始化
            @param  input_model_path ：模型路径
            @param  use_gpu             ：是否使用gpu
            @param  device_id         ：设备id
            @return 返回码 ：0：成功； 其他值：失败
        */
    ResultCode Init(
        const std::string &input_model_path,
        const bool use_gpu,
        const int device_id) override;

    /**
            sdk处理
            @param  req ：sdk输入参数结构体的引用
            @param  rsp    ：sdk输出结果结构体的引用
            @return 返回码 ：0：成功； 其他值：失败
        */
    ResultCode Run(const SegmentationRequest &req, WenTaiZhengMianResponse &rsp);

    std::string Meta(MetaType type) override;

    ResultCode Visualize(const SegmentationRequest &req,
                         const SegmentationResponse &rsp,
                         cv::Mat &image) override;

   private:
    class Impl;
    std::shared_ptr<Impl> impl_;

    ResultCode Run(const SegmentationRequest &req, SegmentationResponse &rsp) override {
        return ResultCode::Success;
    }
};

}  // namespace smartmore

#endif
