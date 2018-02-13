/**
 * 接口 drawAPI
 */
interface DrawAPI {
  fun drawCircle (radius: Int, x : Int, y : Int)
}

/**
 * 实现类红圈
 */
class RedCircle : DrawAPI {
  override fun drawCircle(radius: Int, x: Int, y: Int) {
    print("Drawing Circle[ color: red, radius: "+ radius +", x: " +x+", "+ y +"]")
  }
}

/**
 * 实现类绿圈
 */
class GreenCircle : DrawAPI {
  override fun drawCircle (radius: Int, x: Int, y: Int) {
    print("Drawing Circle[ color: green, radius: " + radius +", x: " +x+", "+ y +"]")
  }
}

/**
 * 抽象类 shape
 */
abstract class Shape (dAPI : DrawAPI) : DrawAPI {
   protected drawAPI : DrawAPI = dAPI; 
   public abstract fun draw(); 
}

/**
 * 实现类Circle
 */ 
class Circle (posX : Int, posY : Int, circleRadius : Int, drawAPI : DrawAPI) : Shape (drawAPI) {
  private x : Int = posX;
  private y : Int = posY;
  private radius : Int = circleRadius;
  
  public fun draw () {
    drawAPI.drawCircle(radius, x ,y)
  } 
}

