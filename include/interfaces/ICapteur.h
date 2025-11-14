// ICapteur.h
#ifndef ICAPTEUR_H
#define ICAPTEUR_H

class IBestiole;

class ICapteur {
 public:
  virtual ~ICapteur() {}
  virtual bool Detect(IBestiole& b) = 0;
  virtual void draw() = 0;
};
#endif  // ICAPTEUR_H