// 接口 媒体播放器
interface MediaPlayer {
  public fun play (audioType: String, fileName: String)
}

// 接口，先进播放器
interface AdvancedMediaPlayer {
  public fun playVlc (fileName: String)
  public fun playMp4 (fileName: String)
}

// Vlc播放器
public class VlcPlayer : AdvancedMediaPlayer {
   override public playVlc(fileName: String) {
      print("Playing vlc file. Name: "+ fileName);        
   }
   override public playMp4(fileName: String) {
      // 什么也不做
   }
}

// MP4 播放器
public class Mp4Player : AdvancedMediaPlayer{
   override public playVlc(fileName: String) {
      //什么也不做
   }
   override public playMp4(fileName: String) {
      print("Playing mp4 file. Name: "+ fileName);        
   }
}

public class MediaAdapter : MediaPlayer {
   var advancedMusicPlayer : AdvancedMediaPlayer?;

   constructor (audioType: String){
      if(audioType.equalsIgnoreCase("vlc") ){
         advancedMusicPlayer = VlcPlayer();            
      } else if (audioType.equalsIgnoreCase("mp4")){
         advancedMusicPlayer = Mp4Player();
      }    
   }
   
   override public play(audioType: String, fileName: String) {
      if(audioType == "vlc"){
         advancedMusicPlayer.playVlc(fileName);
      }else if(audioType == "mp4"){
         advancedMusicPlayer.playMp4(fileName);
      }
   }
}

public class AudioPlayer : MediaPlayer {
   var mediaAdapter : MediaAdapter?; 
   
   override public play(audioType: String, fileName: String) {
      if (audioType == "mp3") {
         print("Playing mp3 file. Name: "+ fileName);   
      } else if (audioType == "vlc" || audioType == "mp4") {
         mediaAdapter = MediaAdapter(audioType);
         mediaAdapter.play(audioType, fileName);
      } else {
         print("Invalid media. "+ audioType + " format not supported");
      }
   }   
}
