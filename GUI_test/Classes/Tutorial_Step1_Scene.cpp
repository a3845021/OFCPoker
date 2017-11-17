#include "Tutorial_Step1_Scene.h"
#include "GUICardDealer.h"

USING_NS_CC;

Scene * TutorialStep1::scene()
{
  return TutorialStep1::create();
}

bool TutorialStep1::init()
{
  if (!Scene::init())
    return false;

  drawBackground();
  drawDealButton();
  drawDeck();
  
  return true;
}

void TutorialStep1::drawBackground()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  auto sprite = Sprite::create("BackGround.png");
  sprite->setPosition(Vec2(visibleSize / 2) + origin);
  this->addChild(sprite);
}

void TutorialStep1::drawDealButton()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  m_pDealCardMenuItem = MenuItemImage::create(
    "PlayerDoneEnabled.png",
    "PlayerDoneClicked.png",
    "PlayerDoneDisabled.png",
    CC_CALLBACK_0(TutorialStep1::dealCard, this));

  m_pDealCardMenuItem->setPosition(origin.x - Vec2(m_pDealCardMenuItem->getContentSize() / 2).x + Vec2(visibleSize).x,
    origin.y + Vec2(m_pDealCardMenuItem->getContentSize() / 2).y);
  m_pDealCardMenuItem->setEnabled(true);

  auto menuRun = Menu::create(m_pDealCardMenuItem, nullptr);
  menuRun->setPosition(Vec2::ZERO);
  this->addChild(menuRun, 1);
}

void TutorialStep1::drawDeck()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();

  auto spriteDeck = Sprite::create(
    "cards_back.png"
  );

  spriteDeck->setPosition(origin.x + Vec2(spriteDeck->getContentSize() / 2).x + m_cFramePadding,
    origin.y + Vec2(visibleSize).y - Vec2(spriteDeck->getContentSize() / 2).y - m_cFramePadding);

  addChild(spriteDeck, 2);
}

//cb
void TutorialStep1::dealCard()
{
  drawCardBack();
  drawCardFront();
  animateCardDealing();
}

void TutorialStep1::drawCardBack()
{
  if (!m_pDealtCardBack)
  {
    m_pDealtCardBack = Sprite::create(
      "cards_back.png"
    );
    addChild(m_pDealtCardBack, 3);
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto origin = Director::getInstance()->getVisibleOrigin();
  m_pDealtCardBack->setPosition(origin.x + Vec2(m_pDealtCardBack->getContentSize() / 2).x + m_cFramePadding,
    origin.y + Vec2(visibleSize).y - Vec2(m_pDealtCardBack->getContentSize() / 2).y - m_cFramePadding);
}

void TutorialStep1::drawCardFront()
{
  if (!m_pDealtCardFront)
  {
    m_pDealtCardFront = Sprite::create(
      "cards_Ah.png"
    );
    addChild(m_pDealtCardFront, 4);
  }

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  m_pDealtCardFront->setPosition(origin.x + Vec2(visibleSize).x / 2,
    origin.y + Vec2(visibleSize).y - Vec2(m_pDealtCardFront->getContentSize() / 2).y - m_cFramePadding);
}

void TutorialStep1::animateCardDealing()
{
  auto disableDealBtn = CallFunc::create([this]()
  {
    m_pDealCardMenuItem->setEnabled(false);
  });

  auto origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 startPosition = m_pDealtCardBack->getPosition();
  Vec2 endPosition = m_pDealtCardBack->getPosition() + Vec2(Vec2(visibleSize).x - 2 * m_cFramePadding - Vec2(m_pDealtCardBack->getContentSize()).x, 0);
  auto dealActions = CPoker::GUICardDealer::dealCard(m_pDealtCardFront, m_pDealtCardBack, startPosition, endPosition);

  auto enableDealBtn = CallFunc::create([this]()
  {
    m_pDealCardMenuItem->setEnabled(true);
  });
  auto sequence = Sequence::create(disableDealBtn, dealActions, enableDealBtn, nullptr);

  m_pDealtCardBack->runAction(sequence);
}