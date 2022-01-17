/******************************************************************************
* FILENAME:      IDnnModule.h
*
* AUTHORS:       Cuntian Liu
*
* START DATE:    Friday, 15th January 2021
*
* CONTACT:       cuntian.liu@smartmore.com
******************************************************************************/

#ifndef __IDNN_MODULE_H__
#define __IDNN_MODULE_H__

#include "Common.h"
#include <string>

namespace smartmore
{
    enum class MetaType
    {
        TaskName = 0,
        TaskType = 1,
        Version = 2,
        CreateTime = 3,
        MD5 = 4,
        Config = 5,
        SDKVersion = 6,
        SDKCompileTime = 7
    };
    //!
    //! \class IDnnModule
    //!
    //! \brief Base IDnnModule class for user-implemented layers.
    //!
    class DLL_API IDnnModule
    {
    public:
        IDnnModule() = default;

        virtual ~IDnnModule() = default;

        //!
        //! \brief Get version information of the model.
        //!
        //! \return The version information.
        //!
        //! Version information should include the MD5 of model and the build time of this SDK.
        //! (e.g. "Version: 1.0.0"
        //!       "Model MD5: 87d2c0a12551f0fc807b9a2aec207543"
        //!       "SDK CreateTime: Nov  5 2020 17:00:00")
        //!
        virtual std::string Version() = 0;

        //!
        //! \brief Init Module with given model path.
        //!
        //! \param input_model_path The path of input model.
        //! \param use_gpu Whethre use gpu in subsequent inference.
        //! \param device_id ID of gpu used.
        //!
        //! \return The status of Initialization. OK for success, else non-zero.
        //!
        //! In particular, this function is called prior to any call to Run().
        //!
        virtual ResultCode Init(const std::string &input_model_path,
                                const bool use_gpu,
                                const int device_id) = 0;

        //!
        //! \brief Get Meta information of the model and SDK.
        //!
        //! \param type type of Metatype.
        //!
        //! \return The meta information.
        //!
        virtual std::string Meta(MetaType type) = 0;
    };
} // namespace smartmore

#endif
