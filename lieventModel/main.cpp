#include <iostream>
#include <string.h>
#include "include/event2/event.h"

#include "include/event2/http.h"
#include "include/event2/keyvalq_struct.h"
#include "include/event2/buffer.h"
#include <signal.h>
#include <string>
#define webroot "."
#define webrootindex "index.html"
using namespace std;

void http_cb(struct evhttp_request *request,void *args){

    cout<<" http_cb"<<endl;
    const char *uri = evhttp_request_get_uri(request);
    cout<<"uri: "<<uri<<endl;

    string cmdtype;
    switch (evhttp_request_get_command(request)){
        case EVHTTP_REQ_GET:
            cmdtype="GET";
            break;
        case EVHTTP_REQ_POST:
            cmdtype="POS";
            break;
        default:
            break;
    }
    cout<<"cmdtype: "<<cmdtype<<endl;
    //header
    cout<<">>>>>>>>headers: "<<endl;
    evkeyvalq * headers = evhttp_request_get_input_headers(request);
    for (evkeyval *p =headers->tqh_first;p!=NULL;p=p->next.tqe_next) {
        cout<<"key: "<<p->key<<" value: "<<p->value<<endl;
    }
    //data
    cout<<">>>>>>>>data: "<<endl;
    char data[1024]={0};
    evbuffer *inbuf = evhttp_request_get_input_buffer(request);
    while (evbuffer_get_length(inbuf)){
        int len = evbuffer_remove(inbuf,data,sizeof(data)-1);
        if(len>0){
            cout<<"data: "<<data<<endl;
        }
    }

    //answer


    string filepath = webroot;
    filepath+=uri;
    if (strcmp(uri,"/")==0)
    {
        filepath+=webrootindex;
    }
    FILE *fp = fopen(filepath.c_str(),"rb");
    if (fp==NULL)
    {
        evhttp_send_reply(request,HTTP_NOTFOUND,"",0);
        return;
    }

    //message header
    evkeyvalq *outheader = evhttp_request_get_output_headers(request);
    int pos = filepath.rfind('.');
    string posfix = filepath.substr(pos+1,filepath.size()-(pos+1));
    if(posfix=="jpg"||posfix=="jmp"||posfix=="png"||posfix=="gif"){
        string tmp="image/"+posfix;
        evhttp_add_header(outheader,"Content-Type",tmp.c_str());
    }else if (posfix =="zip") {
        evhttp_add_header(outheader,"Content-Type","application/zip");
    }else if(posfix=="html"){
        evhttp_add_header(outheader,"Content-Type","text/html;charset=UTF8");
    }
    else if(posfix == "css"){
        evhttp_add_header(outheader,"Content-Type","text/css");
    }

    evbuffer *outbuf = evhttp_request_get_output_buffer(request);
    char buf[1024]={0};
    for (;;) {

        int len =fread(buf,1,sizeof(buf),fp);
        if(len<=0)
            break;
        evbuffer_add(outbuf,buf,sizeof(buf));
    }
    fclose(fp);

    evhttp_send_reply(request,HTTP_OK,"",outbuf);
    return;
}
int main() {
    if(signal(SIGPIPE,SIG_IGN) ==SIG_ERR)
        return 0;

    event_base *base = event_base_new();
    if(!base)
    {
        cout<<" create event_base ffailed"<<endl;
        return 0;
    }

    evhttp *evh =  evhttp_new(base);
    if(evhttp_bind_socket(evh,"0.0.0.0",8085)!=0)
    {
        cout<<" bind socket failed"<<endl;
        evhttp_free(evh);
        return 0;

    }

    evhttp_set_gencb(evh,http_cb,0);

    if (base)
        event_base_dispatch(base);


    if(base)
        event_base_free(base);
    if (evh)
        evhttp_free(evh);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}