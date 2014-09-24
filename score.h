#ifndef __SCORE_H__
#define __SCORE_H__

class Score{
  int currentScore;
  int hiScore;
public:
  Score();
  int getScore();
  int getHiScore();
  void setScore(int currentScore);
  void setHiScore(int hiScore);
};
#endif
