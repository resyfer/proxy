#ifndef __CONFIG_H
#define __CONFIG_H

typedef struct proxy {
  char *name;
  char *host;
  char *port;
} proxy_t;

typedef struct settings {
  char *college;
  char *desktop;
  char *os;
  char *shell;

  proxy_t *proxy;
  unsigned proxy_count;

  char** extras;
  unsigned extras_count;
} settings_t;

void
config_parse(settings_t **conf);

#endif