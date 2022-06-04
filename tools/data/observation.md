absolute sensor neigt naar links door code, ipv rechtdoor



absoluut:
```
// Sensor Readout:
sensor.read() > 0.5f ? Dark : Light;
```

relatief:
```
// Sensor Readout:
sensor1.read() - 0.3f > sensor2.read() && sensor1.read() + 0.3f < sensor2.read()  
```