
$(document).ready(function() {


    $('#create').click(() => {
        $('#code').addClass('shown');
        $('#dimmer').addClass('on');
        if ($("#title").val().length < 2) {
            $("#code-title").html("title");
        } else {
            $("#code-title").html($("#title").val());
        }
        $("#code1").html($("#select1").val() + "()");
        $("#code2").html($("#select2").val() + "()");
        $("#code3").html($("#select3").val() + "()");
        $("#code4").html($("#select4").val() + "()");
        $("#code5").html($("#select5").val() + "()");
        $("#code6").html($("#select6").val() + "()");

    })
    $('#dimmer').click(() => {
        $('#code').removeClass('shown');
        $('#dimmer').removeClass('on');
    })
});
