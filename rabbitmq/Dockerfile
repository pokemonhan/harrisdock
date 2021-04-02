FROM rabbitmq:management-alpine

LABEL maintainer="Mahmoud Zalt <mahmoud@zalt.me>"

RUN rabbitmq-plugins enable --offline rabbitmq_management

RUN apk update && \
apk add wget unzip

#RUN apt-get -yqq update && \
#apt-get install -yqq wget unzip

##############v 3.7##############
#RUN curl https://dl.bintray.com/rabbitmq/community-plugins/3.7.x/rabbitmq_delayed_message_exchange/rabbitmq_delayed_message_exchange-20171201-3.7.x.zip > rabbitmq_delayed_message_exchange-20171201-3.7.x.zip && \
#unzip rabbitmq_delayed_message_exchange-20171201-3.7.x.zip && \
#rm -f rabbitmq_delayed_message_exchange-20171201-3.7.x.zip && \
#mv rabbitmq_delayed_message_exchange-20171201-3.7.x.ez plugins/

##############v 3.8##############
#problems
#Problem reading some plugins: [{"/usr/lib/rabbitmq/plugins/rabbitmq_delayed_message_exchange-3.8.0.ez",
#                                {invalid_ez,einval}}]
# figured it out. I was using curl -O to download the file, which was causing the file to be changed during transfer. Not 100% sure why but it must have been mangling the request somehow. I tried wget and the checksums matched and I was able to start rabbit again. Thanks for the help!
RUN wget https://github.com/rabbitmq/rabbitmq-delayed-message-exchange/releases/download/3.8.9/rabbitmq_delayed_message_exchange-3.8.9-0199d11c.ez && \
ls -la && \
#chmod o+x rabbitmq_delayed_message_exchange-3.8.9-0199d11c.ez && \
chown rabbitmq:rabbitmq rabbitmq_delayed_message_exchange-3.8.9-0199d11c.ez && \
ls -la && \
mv rabbitmq_delayed_message_exchange-3.8.9-0199d11c.ez plugins/rabbitmq_delayed_message_exchange-3.8.9.ez && \
ls -la plugins/

RUN rabbitmq-plugins enable --offline rabbitmq_delayed_message_exchange

EXPOSE 4369 5671 5672 15671 15672 25672
