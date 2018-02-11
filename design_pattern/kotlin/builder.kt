/**
 * 接口 Item
 */
interface Item {
  fun name () : String
  fun packing () : Packing
  fun price () : Float
}

/**
 * 接口包装
 */
interface Packing {
  fun packing () : String
}

/**
 * 包装
 */
class Wrapper : Packing {
  override packing (): String {
    return "Wrapper"
  }
}

/**
 * 瓶子
 */
class Bottle : Packing {
  override packing () :String {
    return "Bottle"
  }
}

/**
 * 汉堡
 */
class Burger : Item {
  override name () : String {
    return "Burger"
  }
  
  override price () : Float {
    return 12.75
  }
}

/**
 * 冷饮
 */
 class ColdDrink : Item {
  override name () : String {
    return "ColdDrink"
  }
  
  override price () : Float {
    return 12.75
  }
 }
 
 /**
  * veg汉堡
  */
class VegBurger : Burger {
  override fun price() : Float {
    return 25.0f
  }

  override fun name() : String {
    return "Veg Burger"
  }
}

/**
 * 鸡肉汉堡
 */
class ChickenBurger: Burger {
   override fun price () : Float {
      return 50.5f;
   }

   override fun name () : String {
      return "Chicken Burger";
   }
}

/**
 * 可口可乐
 */
class Coke : ColdDrink {
  override fun price () : Float {
    return 35.0f
  }
  
  override fun name () : String{
    return "Coke"
  }
}

/**
 * 百事可乐
 */
class Pepsi : ColdDrink {
  override fun price () : Float {
    return 35.0f
  }
  
  override fun name () : String{
    return "Pepsi"
  }
}

