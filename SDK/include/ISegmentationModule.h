/*******************************************************************************
 *  FILENAME:      ISegmentationModule.h
 *
 *  AUTHORS:       max.ma    START DATE: Friday November 6th 2020
 *
 *  LAST MODIFIED: Sunday, February 7th 2021, 12:16:48 pm
 *
 *  CONTACT:       max.ma@smartmore.com
*******************************************************************************/

#ifndef __ISEGMENTATION_MODULE_H__
#define __ISEGMENTATION_MODULE_H__

#include "IDnnModule.h"
#include <vector>
#include <opencv2/opencv.hpp>

namespace smartmore
{
    //!
    //! \struct SegmentationRequest
    //!
    struct SegmentationRequest
    {
        cv::Mat image;
        std::vector<int> thresholds; //!< The threshold is used to judge the classification.
    };

    //!
    //! \struct SegmentationResponse
    //!
    struct SegmentationResponse
    {
        cv::Mat mask;                     //! The output mask
        std::map<int, std::string> names; //! Types of mask
        QCCode code;                      //! status code
    };

    //!
    //! \class ISegmentationModule
    //!
    //! \brief Base SegmentationModule class for user-implemented layers.
    //!
    class DLL_API ISegmentationModule : public IDnnModule
    {
    public:
        ISegmentationModule() = default;
        virtual ~ISegmentationModule() = default;

        //!
        //! \brief Do inference.
        //!
        //! \param req The origin request.
        //! \param rsp The respnse generates from Run.
        //!
        //! \return The status of Visualization. OK for success, else non-zero.
        //!
        virtual ResultCode Run(const SegmentationRequest &req, SegmentationResponse &rsp) = 0;

        //!
        //! \brief Visualize result.
        //!
        //! \param req The origin request.
        //! \param rsp The respnse generates from Run.
        //! \param image Output image.
        //!
        //! \return The status of Visualization. OK for success, else non-zero.
        //!
        virtual ResultCode Visualize(const SegmentationRequest &req,
                                     const SegmentationResponse &rsp,
                                     cv::Mat &image);
    };

} // namespace smartmore

#endif
