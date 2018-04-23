#### ModelMap 和 ModelAndView 的作用
- Model是包含四个addAttribute和一个merAttribute方法的接口
- ModelMap: 实现了Map接口，包含Map方法。视图层通过request找到ModelMap中的数据
- ModelAndView: 是包含ModelMap 和视图对象的容器。正如名字暗示的一样既包含模型也包含视图，而ModelMap只是包含模型的信息
