[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=22774294)
# 🔊 Beat Box Lights  
Advanced C++ Embedded Systems Lab  

## Overview  
In this lab, we built an embedded system using Arduino that listens to sound through a microphone sensor, estimates beat intensity, lights up a 5-LED level meter, detects beats using threshold + cooldown logic, and plays a short click sound on a piezo buzzer when a beat is detected.

This project reinforced:

- Multi-file C++ structure  
- Header and source file separation  
- Encapsulation  
- Real-time signal processing  
- Parameter tuning  
- Clean software engineering design  

---

## 🟢 Step 1 — Microphone Signal + Baseline Reflection  

### What was your baseline value in a quiet room?  
In a quiet room, my baseline stayed around 510 to 515. It was close to 512 since that’s the middle of the analog range.

### Why do we update the baseline slowly instead of setting it directly to raw?  
We update it slowly so it represents the average background sound instead of reacting to every single noise. If we set it equal to raw every time, it would just follow the sound instantly and we wouldn’t be able to detect changes properly.

### What would happen if the baseline updated too quickly?  
If it updated too fast, the system wouldn’t detect beats correctly because the baseline would rise with loud sounds. That means the difference between raw and baseline would stay small and beats wouldn’t stand out.

---

## 🟡 Step 2 — LED Meter Reflection  

### Why does LightUp not know anything about microphones?  
LightUp only controls the LEDs. It doesn’t care where the number comes from. It just takes a level and turns LEDs on or off based on that value.

### What design principle does this demonstrate?  
This shows encapsulation and separation of concerns. Each class has one specific job and doesn’t depend on the internal details of other classes.

### If you wanted to change to 10 LEDs, what would need to change?  
We would just update the pin array and the count when creating the LightUp object. The class itself wouldn’t need to be rewritten.

---

## 🔵 Step 3 — Beat Detection Reflection  

### What happens if cooldown is removed?  
If cooldown is removed, it would detect multiple beats for one actual beat because the signal stays above the threshold for a short time. It would trigger repeatedly and not feel accurate.

### What happens if threshold is too low?  
If the threshold is too low, the system will detect beats from random noise or small sounds. It becomes way too sensitive.

### Why is time (millis()) important in embedded systems?  
Time is important because embedded systems run continuously. We use millis() to control when events happen without stopping the whole program.

---

## 🟣 Step 4 — SoundDevice Reflection  

### How does intensity affect the sound?  
Higher intensity increases the frequency and duration of the click. So louder beats create a higher pitched and slightly longer beep.

### Why is tone() sufficient for this lab instead of playing WAV files?  
We only need a short click sound, so tone() is simple and efficient. Playing WAV files would require more memory and extra hardware support.

---

## 🔴 Step 5 — Main Program Reflection  

### How is std::vector used in this system?  
In this version, std::vector is not used. Instead, we use a fixed size array to store recent levels because the Arduino Uno has limited memory.

### What does smoothing accomplish?  
Smoothing averages recent sound levels so the LEDs don’t flicker rapidly. It makes the output look cleaner and more stable.

### What would happen if smoothing was removed?  
If smoothing was removed, the LEDs would react to every tiny sound change. The meter would jump around constantly and look noisy.

---

## 🎯 Final Thoughts  

This project helped me understand how to structure an embedded system using multiple C++ files while keeping everything organized. Each class had a clear responsibility, which made the system easier to debug and adjust. It was a good example of combining hardware, real-time processing, and software design into one working system.
