<h1 class="contract">joincoop</h1>
<!DOCTYPE html>
<html lang="en"> 
  <head>
    <meta charset="utf-8">
    <title>Заявление //заголовок</title>
    <meta name="description" content="Контракт предоставляет форму заявления на вступление в цифровой кооператив //краткое описание">
    <meta name="version" content="0.0.1">
  </head>
  <body>

<h1>Заявление</h1>
<p>о приёме {% if member.is_organization %}юридического{% else %}физического{% endif %} лица в пайщики {{coop.shortname}}.</p>
<h2>Заявитель:</h2>
<ul>
  {% if member %}
    <li>{{ member.shortname }} {% trans ‘represented by’ %} {{ user.first_name }} {{ user.last_name }}, {{ user.position }}</li>
  {% else %}
    <li>{{ user.first_name }} {{ user.last_name }}</li>
  {% endif %}
</ul>

<p>Прошу принять меня в пайщики потребительского кооператива {{ coop.shortname }}, далее по тексту заявления "Общество". Подтверждаю, что с Уставом и иными публичными нормативными документами Общества ознакомлен(а).</p>

<p>Став пайщиком Общества, обязуюсь соблюдать требования Устава и иных публичных нормативных документов Общества и выполнять обязанности члена Общества, а также уполномачиваю Председателя кооперативного участка "Центр" принимать участие с правом голоса в Общих собраниях уполномоченных Общества, на период моего членства в Обществе при собственноручно мною указанном кооперативном участке. </p>

<p>Обязуюсь своевременно внести в Общество {% if coop.initial %} вступительный {{ coop.initial }} {{ coop.currency }}{% endif %} {% if coop.minimum %} и минимальный паевой {{ coop.minimum }} {{ coop.currency }}{% endif %} взносы в порядке, предусмотренном Уставом Общества.</p>

<p>Выражаю своё согласие на генерацию моей внутренней ЭЦП (Электронно-Цифровой Подписи) для подписания документооборота в моём Личном Кабинете, в рамках внутренней деятельности Общества, в соответствии с Положением о внутренней ЭЦП Общества.</p>

<p>Выражаю своё согласие с тем, что информация, отправляемая Обществом в sms-сообщениях на указанный мной номер телефона или в сообщениях на указанный мной адрес электронной почты или в сообщениях телеграм-бота, привязанного к моему телефону, приравняется к уведомлению меня Обществом в письменной форме.</p>

  </body>
</html>
