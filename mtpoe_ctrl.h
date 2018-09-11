#ifndef _MTPOE_CTRL
#define _MTPOE_CTRL

//файл для общения с spidev модулем
#define DEFAULT_DEV_FILE "/dev/spidev0.2"
//ключ субконфига uci->network в котором находятся настройки PoE
#define MTIK_POE_UCI_CONFIG_KEY "mtik_poe"
//сколько всего PoE портов
#define POE_PORTS_N 4

int spidev_fd = -1;
uint8_t *spidev_query(int, uint8_t, uint8_t, uint8_t);


int need_exit = 0; //еще не пора выходить

/* переменные со значениями опций.
   не забывай при добавлении новой переменной так же вписывать
   ее в opt_X enum и my_options
*/

int dumpvars = 0; //вывод значений переменных
char action[255] = "noop"; //действие(add, del, ...)
char dev_file[30] = DEFAULT_DEV_FILE; //файл для общения с spidev модулем
int period = 0; //период повторения главного цикла
int verbose = 0; //быть более разговорчивым
int port = -1; //номер порта. используется для set_poe
int val = -1; //значение. напрнимер 0, 1 или 2 для set_poe
int version = 0; //нужно показать версию и выйти

int single = 1; //запрос о выводе данных касается единичной команды или их множество
char *err_descr = NULL; //подробное описание произошедшей ошибки
int scop = 1; //уже была напечатана открывающаяся скобка

//структура с описанием нашей опции
struct my_option{
  const char *name;
  int id;
  char type;
  void* ptr;
  int l_min;
  int l_max;
};

typedef void (*my_action_cb)(void);

//структура с описанием значения опции action
struct my_action_opt{
  const char *name;
  my_action_cb cb;
};

/* имена опций на которые реагирует программа */
enum {
  opt_dumpvars,
  opt_action,
  opt_dev_file,
  opt_period,
  opt_verbose,
  opt_port,
  opt_val,
  opt_version,
  opt_MAX
};

#include "params.h"

//список известных нам опций
const struct my_option my_options[] = {
  define_flag_opt(dumpvars),
  define_str_opt(action),
  define_str_opt(dev_file),
  define_int_opt(period, 0, 3600),
  define_flag_opt(verbose),
  define_int_opt(port, 0, 3),
  define_int_opt(val, 0, 0xFFFF),
  define_flag_opt(version),
  define_empty_opt()
};

#endif /* _MTPOE_CTRL */