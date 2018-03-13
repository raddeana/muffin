#### 模板模式
在模板模式（Template Pattern）中，一个抽象类公开定义了执行它的方法的方式/模板

#### Game
```java
public abstract class Game {
   abstract void initialize ();
   abstract void startPlay ();
   abstract void endPlay ();

   // 模板
   public final void play(){
      // 初始化游戏
      initialize();
      // 开始游戏
      startPlay();
      // 结束游戏
      endPlay();
   }
}
```

#### Cricket
```java
public class Cricket extends Game {
   @Override
   void endPlay() {
      System.out.println("Cricket Game Finished!");
   }
   @Override
   void initialize() {
      System.out.println("Cricket Game Initialized! Start playing.");
   }
   @Override
   void startPlay() {
      System.out.println("Cricket Game Started. Enjoy the game!");
   }
}
```

#### Football
```java
public class Football extends Game {
   @Override
   void endPlay () {
      System.out.println("Football Game Finished!");
   }
   @Override
   void initialize () {
      System.out.println("Football Game Initialized! Start playing.");
   }
   @Override
   void startPlay () {
      System.out.println("Football Game Started. Enjoy the game!");
   }
}
```
