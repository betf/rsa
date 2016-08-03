#define DBG(...) do{ debug("[%s:%s@%d] ", __FILE__, __FUNCTION__, __LINE__); debug(__VA_ARGS__); } while(0);
