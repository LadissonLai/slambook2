#include <iostream>
#include <string>
#include <chrono> //计时
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
    std::string img_path = "./ubuntu.png";
    // 读取图片
    cv::Mat image = cv::imread(img_path);
    if (image.data == nullptr)
    {
        std::cerr << "file is not exist..." << std::endl;
        return 1;
    }
    // 访问图片的基本参数: 宽高通道数
    std::cout << " width: " << image.cols << " height: " << image.rows << " channels:" << image.channels() << std::endl;
    cv::imshow("my image", image);
    cv::waitKey(); // 参数为，延迟多少秒后自动关闭

    // 遍历图像1:使用图像行指针。
    // 总结：按照这种方式可以推断，opencv图形的存储就是一个一维数组，而不是三维数组
    using namespace std::chrono;
    steady_clock::time_point start = steady_clock::now();
    for (size_t y = 0; y < image.rows; y++)
    {
        unsigned char *row_ptr = image.ptr<unsigned char>(y);
        for (size_t x = 0; x < image.cols; x++)
        {
            unsigned char *channel_ptr = &row_ptr[x * image.channels()];
            for (size_t c = 0; c < image.channels(); c++)
            {
                unsigned char data = channel_ptr[c];
            }
        }
    }
    steady_clock::time_point end = steady_clock::now();
    milliseconds time_span = duration_cast<milliseconds>(end - start);
    std::cout << "image.ptr cost time is:" << time_span.count() << "ms" << std::endl;

    // 遍历图像2：
    start = steady_clock::now();
    for (size_t y = 0; y < image.rows; y++)
    {
        for (size_t x = 0; x < image.cols; x++)
        {
            if (image.channels() == 3)
            {
                uchar b = image.at<cv::Vec3b>(y, x)[0];
                uchar g = image.at<cv::Vec3b>(y, x)[1];
                uchar r = image.at<cv::Vec3b>(y, x)[2];
            }
        }
    }
    end = steady_clock::now();
    time_span = duration_cast<milliseconds>(end - start);
    std::cout << "image.at cost time is:" << time_span.count() << "ms" << std::endl;

    // 使用迭代器
    auto iter = image.begin<cv::Vec3b>();
    auto iter_end = image.end<cv::Vec3b>();
    start = steady_clock::now();
    while (iter != iter_end)
    {
        // 访问元素
        (*iter)[0];
        (*iter)[1];
        (*iter)[2];
        iter++;
    };
    end = steady_clock::now();
    time_span = duration_cast<milliseconds>(end - start);
    std::cout << "image iter cost time is:" << time_span.count() << "ms" << std::endl;

    return 0;
}
