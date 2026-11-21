#ifndef TOKEN_H
#define TOKEN_H

extern int shared_counter;
int next_extern_token(void);
int next_token(void);
int auto_token(void);

#endif
