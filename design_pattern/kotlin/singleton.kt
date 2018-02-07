class Singleton {
    private var singletonInstance : Singleton ?= null

    @Synchronized fun getInstance : Singleton () {
      if (instance == null) {
        instance = Singleton ();
      }
      
      return instance;
    }
}

