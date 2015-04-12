#include "ScorePanel.h"
#include "World.h"


ScorePanel::ScorePanel(World * world)
	:rect_(sf::Vector2f(world->score_panel().x * world->cell_size(), world->window_size().y))
	, world_(world)
	, font_score(world->font_())
	, score_input(0)
	, texture(world->texture_fon_())
{
	rect_.setPosition(world_->window_size().x, 0);
	rect_.setTexture(&texture);

	input_ << world_->get_snake()->get_score();
	text_score.setFont(font_score);
	text_score.setCharacterSize(world_->cell_size());
	text_score.setColor(sf::Color::White);
	text_score.setPosition(world_->window_size().x + world_->cell_size(), 0);
	text_score.setString("Score: \n" + input_.str());
}

void ScorePanel::update_score()
{
	if (world_->get_snake()->get_score() > score_input)
	{
		input_.str("");
		input_.clear();
		score_input++;
		input_ << world_->get_snake()->get_score();
		text_score.setString("Score: \n" + input_.str());
	}
}

void ScorePanel::draw(sf::RenderWindow &window) const
{
	window.draw(rect_);
	window.draw(text_score);
}
