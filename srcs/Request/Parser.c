#include "Request.h"
#include "Generic.h"
#include <stdio.h>
#include <string.h>

static string getSubject(string message) {
    int i;
    int start;

    i = 0;
    start = -1;
    while (message[i] != '\0')
    {
        if (message[i] == ' ' || message[i] == '\t')
        {
            start = ++i;
            break;
        }
        ++i;
    }
    if (start == -1)
        return NULL;
    return strndup(message + start, strlen(message) - start);
}

static string cutMessage(string message) {
    string str;
    size_t i;

    i = 0;
    while (message[i] && message[i] != ' ')
        i++;
    str = xmalloc((size_t) (i + 1));
    strncpy(str, message, i);
    str[i] = '\0';
    return (str);
}

static void reqMove(Request *req) {
    req->requestedAction = MOVE;
    req->actionSubject = NULL;
}

static void reqRotateRight(Request *req) {
    req->requestedAction = ROTATE;
    req->actionSubject = xmalloc(sizeof(char) * 6);
    req->actionSubject = strdup("droite");
}

static void reqRotateLeft(Request *req) {
    req->requestedAction = ROTATE;
    req->actionSubject = xmalloc(sizeof(char) * 6);
    req->actionSubject = strdup("gauche");
}

static void reqLook(Request *req) {
    req->requestedAction = LOOK;
    req->actionSubject = NULL;
}

static void reqLookInventory(Request *req) {
    req->requestedAction = LOOK_INVENTORY;
    req->actionSubject = NULL;
}

static void reqExpulse(Request *req) {
    req->requestedAction = EXPULSE;
    req->actionSubject = NULL;
}

static void reqIncant(Request *req) {
    req->requestedAction = INCANT;
    req->actionSubject = NULL;
}

static void reqFork(Request *req) {
    req->requestedAction = FORK;
    req->actionSubject = NULL;
}

static void reqAskSlot(Request *req) {
    req->requestedAction = ASK_SLOT;
    req->actionSubject = NULL;
}

static void reqTake(Request *req) {
    string sub;
    req->requestedAction = TAKE;
    sub = getSubject(req->message);
    req->actionSubject = sub;
}

static void reqDrop(Request *req) {
    string sub;
    req->requestedAction = DROP;
    sub = getSubject(req->message);
    req->actionSubject = sub;
}

static void reqBroadcast(Request *req) {
    string sub;
    req->requestedAction = BROADCAST;
    sub = getSubject(req->message);
    req->actionSubject = sub;
}

static void reqDeath(Request *req) {
    req->requestedAction = DIE;
    req->actionSubject = NULL;
}

static const struct s_command_string requestsArray[] =
        {
                {"avance",      &reqMove,           7},
                {"droite",      &reqRotateRight,    7},
                {"gauche",      &reqRotateLeft,     7},
                {"voir",        &reqLook,           7},
                {"inventaire",  &reqLookInventory,  1},
                {"prend",       &reqTake,           7},
                {"pose",        &reqDrop,           7},
                {"expulse",     &reqExpulse,        7},
                {"broadcast",   &reqBroadcast,      7},
                {"incantation", &reqIncant,         300},
                {"fork",        &reqFork,           42},
                {"connect nbr", &reqLook,           0},
                {"-",           &reqDeath,          0}
        };

Request *ParseRequest(Request *request) {
    int i;
    string cut;

    i = 0;
    cut = cutMessage(request->message);
    while (i <= 12)
    {
        if (strcmp(cut, requestsArray[i].str) == 0) {
            request->absoluteActionTime = requestsArray[i].absoluteTime;
            requestsArray[i].doAction(request);
        }
        ++i;
    }
    xfree(cut, strlen(cut));
    return request;
}
